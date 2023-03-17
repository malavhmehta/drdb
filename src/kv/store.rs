use crate::error::{Error, Result};

pub mod iter {
    /// The bounds used for [`Range`], where Included/Excluded bounds carry the usual meaning, and
    /// a prefix bound, when used at the start, is equivalent to an
    pub enum Bounds {
        Included(Vec<u8>),
        Excluded(Vec<u8>),
        Prefix(Vec<u8>),
    }

    /// The position of the iterator relative to the scan range.
    pub enum Position {
        Before,
        Between,
        After,
    }

    /// The range used to scan through a store (for generating bounds in the iterator).
    pub struct Range {
        start: Bounds,
        end: Bounds,
    }

    impl Range {
        pub fn start(&self) -> &[u8] {
            match &self.start {
                Bounds::Included(b) | Bounds::Excluded(b) | Bounds::Prefix(b) => &b,
            }
        }

        pub fn end(&self) -> &[u8] {
            match &self.end {
                Bounds::Included(b) | Bounds::Excluded(b) | Bounds::Prefix(b) => &b,
            }
        }

        /// Returns the position of the record with respect to this range.
        pub fn pos(&self, record: &[u8]) -> Position {
            match &self.start {
                Bounds::Included(b) | Bounds::Prefix(b) => {
                    if record < &b {
                        return Position::Before;
                    }
                }
                Bounds::Excluded(b) => {
                    if record <= &b {
                        return Position::Before;
                    }
                }
            }
            match &self.end {
                Bounds::Included(b) => {
                    if record > &b {
                        return Position::After;
                    }
                }
                Bounds::Excluded(b) => {
                    if record >= &b {
                        return Position::After;
                    }
                }
                Bounds::Prefix(b) => {
                    if record.len() < b.len() {
                        return Position::After;
                    }
                    for i in 1..b.len() {
                        if b[i] != record[i] {
                            return Position::After;
                        }
                    }
                }
            }
            return Position::Between;
        }
    }
}
