"""Self-hosted web asset delivery for Higurashi Daybreak (issue #4).

The service has two halves and one rule:

  prepare  reads the host's own install, resolves the .DAT archives exactly the
           way the native asset layer does, and writes a prepared tree plus a
           versioned catalog next to it.
  serve    hands the web client and individual catalogued assets to a browser
           from one origin.

The rule: game data never enters Git or the Docker image. Everything under the
prepared directory is derived from the host's install and is meant to be a
volume, not a build artifact.

PROVENANCE. The archive handling here (precedence order, duplicate resolution,
case-insensitive matching, the XOR payload keys) is *recovered* — it is the same
rule the exe implements and the same rule `src/assets/dat_bundle.{h,cpp}` ports.
The delivery design around it (catalog shape, grouping, HTTP surface) is a
*port decision* for this issue.
"""

__all__ = ["bundles", "catalog", "groups", "server"]
