set(srsc)
set(includes)

list(APPEND includes
    "."
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/fft"
)

list(APPEND srsc
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/adjust_global_gain.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/al_fec_fl.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/apply_global_gain.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/ari_codec.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/attack_detector.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/constants.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/cutoff_bandwidth.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/dct4.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/dec_entropy.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/dec_lc3_fl.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/detect_cutoff_warped.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/enc_entropy.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/enc_lc3_fl.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/estimate_global_gain.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/fft.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/imdct.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/lc3.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/ltpf_coder.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/ltpf_decoder.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/mdct_shaping.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/mdct.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/near_nyquist_detector.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/noise_factor.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/noise_filling.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/olpa.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/pc_apply.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/pc_classify.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/pc_main.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/pc_update.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/per_band_energy.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/plc_classify.c"

    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/setup_enc_lc3.c"

    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/fft/cfft.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/fft/iis_fft.c"
    "LC3plus_ETSI_src_v172062927c2_20210930/src/floating_point/fft/iisfft.c"

    "esp_lc3plus.c"
)


idf_component_register(SRCS ${srsc}
                    INCLUDE_DIRS ${includes}
                    )