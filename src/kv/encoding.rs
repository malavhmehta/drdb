use crate::error::{Error, Result};

/// The number of bytes in the encoded byte representation that are used to store the metadata for
/// these bytes.
pub const METADATA_LENGTH: usize = 2;

/// The maximum number of bytes that can be stored in a single record. Currently, every byte in the
/// metadata is used to store the number of bytes with the associated record. Thus, the maximum
/// byte count for a single record is 2^([`METADATA_LENGTH`] * 8) - 2, since metadata `0x0000` is
/// used to represent a tombstone value.
pub const MAX_RECORD_LENGTH: usize = pow(2, METADATA_LENGTH * 8) - 2;

/// Encodes a slice of bytes into a representation suitable for on-disk storage. The resulting
/// encoding is a vector bytes where the first [`METADATA_LENGTH`] bytes store the metadata
/// associated with the `input`, and the remaining bytes store the `input` themselves. Returns an
/// error if the length of the input exceeds the [`MAX_RECORD_LENGTH`].
pub fn encode_bytes(input: &[u8]) -> Result<Vec<u8>> {
    let mut encoded_bytes = vec![];
    if input.len() > MAX_RECORD_LENGTH {
        return Err(format!(
            "the length of the input bytes, {}, is greater than the max allowed length of {} bytes",
            input.len(),
            MAX_RECORD_LENGTH
        )
        .into());
    }
    let input_length = input.len() as u16;
    encoded_bytes.extend_from_slice(&*input_length.to_be_bytes());
    encoded_bytes.extend_from_slice(input);
    Ok(encoded_bytes)
}

/// Decodes the length of a slice of bytes from the `metadata`. The returned length is a usize
/// denoting the minimum number of extra bytes that need be read so that the record can be decoded.
/// Returns an error if not enough metadata bytes are supplied.
pub fn decode_length(metadata: &[u8]) -> Result<usize> {
    if metadata.len() < METADATA_LENGTH {
        return Err(format!(
            "insufficient metadata bytes given: {} instead of {}",
            metadata.len(),
            METADATA_LENGTH
        )
        .into());
    }
    let mut length = u16::from_be_bytes(metadata[..METADATA_LENGTH].try_into()?);
    if length >= 1 {
        length -= 1;
    }
    Ok(length as usize)
}

/// Decodes bytes from the encoded representation. If the record is a tombstone value, then returns
/// `None`. Otherwise, it returns a new copy of the decoded bytes.
pub fn decode_bytes(encoded: &[u8]) -> Result<Option<Vec<u8>>> {
    let metadata = &encoded[..METADATA_LENGTH];
    if metadata == vec![0x00, 0x00] {
        return Ok(None);
    }

    let length = decode_length(metadata)?;
    if encoded.len() != METADATA_LENGTH + length {
        return Err(format!(
            "insufficient bytes given: {} instead of {}",
            encoded.len(),
            length
        )
        .into());
    }
    Ok(Some(Vec::from(&encoded[METADATA_LENGTH..])))
}
