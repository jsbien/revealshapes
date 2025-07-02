# Changelog

This changelog tracks modifications made in the present fork of https://github.com/rmast/revealshapes.
Earlier changes are not included.

1. **Fix: Correct page numbering (use 1-based index)**  
   [Commit `4ac2fcb`](https://github.com/jsbien/revealshapes/commit/4ac2fcb9355b0c4dc81fa8711c0d6d4426c1f861)

2. **Doc: Add AUTHORS and CONTRIBUTING.md**  
   [Commit `5e2b27f`](https://github.com/jsbien/revealshapes/commit/5e2b27f17ad5e88b4fdc6aee1f0aa1a8f4fba61f)

3. **Doc: Convert screenshot annotations to Markdown (numbered)**  
   [Commit `b72f98b`](https://github.com/jsbien/revealshapes/commit/b72f98bbbd72d543d8821a12429f4eac1c14c117)

4. **Cleanup: Remove stale jb2cmp/.deps directory and .Po dependency files**  
   [Commit `0ab4376`](https://github.com/jsbien/revealshapes/commit/0ab43768283758a1e7db54fa2e36dde723b04b41)  
   These files referenced previously removed tools (`classify`, `cuts`, `frames`, etc.) and were leftover from an old build system.

5  Added technical overview documentation [58b7460]
  - Created docs/overview.md describing the purpose, usage, and structure of the revealshapes tool.
