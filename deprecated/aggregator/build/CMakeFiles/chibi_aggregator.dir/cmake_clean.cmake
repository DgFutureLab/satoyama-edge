file(REMOVE_RECURSE
  "chibi_aggregator.pdb"
  "chibi_aggregator.elf"
)

# Per-language clean rules from dependency scanning.
foreach(lang)
  include(CMakeFiles/chibi_aggregator.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
