# Edge Addition Planarity Suite (vendored)

Upstream: https://github.com/graph-algorithms/edge-addition-planarity-suite
Version:  tag `Version_5.1.0.0` (commit 30d63f809d4fcf947c597af1148fcaae7850ccf7, 2026-09-08)
          https://github.com/graph-algorithms/edge-addition-planarity-suite/tree/Version_5.1.0.0/c/graphLib
Author:   John M. Boyer
License:  BSD-3-Clause, see `LICENSE.TXT`

Every file under `c/graphLib/` is a byte-for-byte copy of the upstream file at
that tag (same relative path), so the lineage can be checked with

    git clone --branch Version_5.1.0.0 https://github.com/graph-algorithms/edge-addition-planarity-suite
    diff -r edge-addition-planarity-suite/c/graphLib c/graphLib   # prints only "Only in upstream" lines

Only the subset of `graphLib` needed for `gp_Embed(theGraph, EMBEDFLAGS_PLANAR)`
is vendored:

* omitted: `graphLib.[ch]` (umbrella header that pulls in everything below),
  `io/` except `strbuf.[ch]` (graph file formats), `homeomorphSearch/*.c`
  (K_{2,3}/K_{3,3}/K_4 search extensions), `planarityRelated/graphDrawPlanar*.c`
  (visibility drawings; depend on `io/`);
* kept: the core graph structure (`graph.c`, `graphDFSUtils.c`, `lowLevelUtils/`,
  `extensionSystem/`), the planarity embedder and Kuratowski-subgraph isolator
  (`planarityRelated/graphEmbed.c`, `graphNonplanar.c`, `graphIsolator.c`,
  `graphPlanarity*.c`), the outerplanarity extension (`graph.c`/`graphEmbed.c`
  reference it), `graphTests.c` and the headers of the omitted extensions that
  `graphEmbed.c` includes.

No vendored file is modified.  All adaptations live in `../correct.cpp`:

* the `.c` files are compiled as C++17 in one translation unit (`#include`d);
* `USE_0BASEDARRAYS` is defined before the includes to select the library's
  0-based vertex/edge indexing (`lowLevelUtils/appconst.h`) instead of the
  default 1-based one;
* definitions of the four extension-ID globals (`DRAWPLANAR_ID`,
  `K23SEARCH_ID`, `K33SEARCH_ID`, `K4SEARCH_ID`) and of the two graph-I/O hooks
  `_ReadPostprocess`/`_WritePostprocess`, whose upstream definitions live in
  omitted files (`graph.c`/`graphEmbed.c` reference them but the planar
  embedding path never calls them);
* a macro shim around the inclusion of `graphEmbed.c`, because
  `_gp_EmbedFlagsValid()` passes `(void *)&context` to
  `gp_FindExtension(graphP, int, void **)`, which is valid C but not C++.
* `-Wdeprecated-declarations` is silenced around the inclusion of
  `io/strbuf.c`, whose `sb_ConcatInt()` calls `sprintf()`, which Apple's SDK
  marks deprecated (the suite is compiled with `-Werror`).
