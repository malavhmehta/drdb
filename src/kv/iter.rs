use crate::error::{Error, Result};
use std::cmp::Ordering;
use std::collections::BinaryHeap;

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

pub trait Iter {
    /// Advances the iterator to the next valid key-value pair, and returns an owned key.
    fn next_key(&mut self) -> Option<Vec<u8>>;

    /// Gets the copied value for the current key, or None if there is no current key.
    fn cur_value(&mut self) -> Option<Vec<u8>>;
}

/// Structure for entries stored in the `iter_heap` of [`IterGroup`] with a custom implementation
/// of [`Ord`] that allows the smallest `key` with the smallest `iter_idx` to be popped first from
/// a [`BinaryHeap`].
struct IterGroupHeapEntry {
    key: Vec<u8>,
    iter_idx: usize,
}

impl Eq for IterGroupHeapEntry {}

impl PartialEq<Self> for IterGroupHeapEntry {
    fn eq(&self, other: &Self) -> bool {
        self.cmp(other) == Ordering::Equal
    }
}

impl PartialOrd<Self> for IterGroupHeapEntry {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl Ord for IterGroupHeapEntry {
    fn cmp(&self, other: &Self) -> Ordering {
        other
            .key
            .cmp(&self.key)
            .then_with(|| other.iter_idx.cmp(&self.iter_idx))
    }
}

/// Collapses a group of iterators into a single iterator.
pub struct IterGroup {
    iters: Vec<Box<dyn Iter>>,
    iter_heap: BinaryHeap<IterGroupHeapEntry>,
}

impl IterGroup {
    /// Creates a new [`IterGroup`].
    ///
    /// *NOTE*: The `iters` MUST be in order of priority. That is, when two different iterators
    /// `iters[i]` and `iters[j]`, with `i` < `j`, have the same key, then only `iters[i]`, that is,
    /// the iterator with the lower index, is considered as the "real" iterator for this key. The
    /// other iterators are advanced to their next key, and their current values are disregarded.  
    pub fn new(mut iters: Vec<Box<dyn Iter>>) -> Self {
        let mut iter_heap = BinaryHeap::new();
        for (i, cur_iter) in iters.iter_mut().enumerate() {
            if let Some(key) = cur_iter.next_key() {
                iter_heap.push(IterGroupHeapEntry { key, iter_idx: i })
            }
        }
        IterGroup { iters, iter_heap }
    }
}

impl Iter for IterGroup {
    fn next_key(&mut self) -> Option<Vec<u8>> {
        if let Some(IterGroupHeapEntry { key: cur_key, .. }) = self.iter_heap.peek() {
            let cur_key = cur_key.clone();
            while let Some(IterGroupHeapEntry { key, .. }) = self.iter_heap.peek() {
                if key != &cur_key {
                    break;
                }
                if let Some(IterGroupHeapEntry { iter_idx, .. }) = self.iter_heap.pop() {
                    if let Some(new_key) = self.iters[iter_idx].next_key() {
                        self.iter_heap.push(IterGroupHeapEntry {
                            key: new_key,
                            iter_idx,
                        })
                    }
                }
            }
        }
        match self.iter_heap.peek() {
            None => None,
            Some(IterGroupHeapEntry { key, .. }) => Some(key.clone()),
        }
    }

    fn cur_value(&mut self) -> Option<Vec<u8>> {
        match self.iter_heap.peek() {
            None => None,
            Some(IterGroupHeapEntry { iter_idx, .. }) => self.iters[*iter_idx].cur_value(),
        }
    }
}
