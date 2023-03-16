use std::array::TryFromSliceError;
use std::fmt::{Display, Formatter};
use std::string::FromUtf8Error;

/// Custom error type for `drdb`.
#[derive(Clone, Debug)]
pub struct Error {
    what: String,
}

/// Result using [`Error`] for the error type.
pub type Result<T> = std::result::Result<T, Error>;

impl Display for Error {
    fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
        write!(f, "drdb error: {}", self.what)
    }
}

impl std::error::Error for Error {
    fn description(&self) -> &str {
        self.what.as_str()
    }
}

impl From<&str> for Error {
    fn from(err: &str) -> Self {
        Error {
            what: String::from(err),
        }
    }
}

impl From<String> for Error {
    fn from(err: String) -> Self {
        Error { what: err }
    }
}

impl From<TryFromSliceError> for Error {
    fn from(err: TryFromSliceError) -> Self {
        Error {
            what: err.to_string(),
        }
    }
}

impl From<FromUtf8Error> for Error {
    fn from(err: FromUtf8Error) -> Self {
        Error {
            what: err.to_string(),
        }
    }
}
