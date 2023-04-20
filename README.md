<br/>

![drdb](https://i.ibb.co/cv6syVY/logo.png)

---

![build result](https://github.com/malav-mehta/drdb/actions/workflows/cmake.yml/badge.svg)

#### This project is a work in progress.

## About

### A distributed relational database

`drdb` is a distributed relational database I am working on to
understand database internals and learn how to build performant
distributed systems. Currently, I am expecting to implement a very
small subset of SQL.

### Features

- **Scalability**: Every instance has some clusters over which the
  key space is partitioned. This means that adding more clusters to
  an instance lowers the number of keys stored per cluster,
  decreasing the load on individual nodes.
- **Redundancy**: Each cluster is responsible for its key range, and
  the data for each cluster is replicated across at least three nodes
  using the Raft consensus algorithm.
- **Simple**: Designed to be simple, the core logic of the database
  is built on very few abstractions over the underlying key-value
  storage engine, making each layer flexible.

## Design

### Lifetime of a query

1. A query is created. It is directed to the cluster leader with the
   smallest load.
2. The query is parsed, and translated into a series of primitive
   key-value operations, partitioned by key range.
3. The operations are sent to the cluster head which corresponds to
   the key range for the given operation.
4. The nodes resolve the operations and return the results to the
   node that originated the request.
5. Final processing is done on the originator node, and the result is
   returned to the query creator.

### Acknowledgements

The design for `drdb` is very heavily inspired by
[CockroachDB](https://www.cockroachlabs.com/), particularly very
helpful articles from the
[engineering blog](https://www.cockroachlabs.com/blog/engineering/).

### Tech stack

- C++
- [gRPC](https://grpc.io/) for communication between nodes

## Contact

If you find bugs or have questions, feel free to email me:
[malavhmehta@outlook.com](mailto:malavhmehta@outlook.com).