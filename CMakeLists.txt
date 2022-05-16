set(srsc)
set(includes)

list(APPEND includes
    "."
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point"
)

list(APPEND srsc
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/lc3.c"
    "esp_lc3plus.c"
)


idf_component_register(SRCS ${srsc}
                    INCLUDE_DIRS ${includes}
                    )