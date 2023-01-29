library verilog;
use verilog.vl_types.all;
entity cyclonev_hssi_pma_aux is
    generic(
        enable_debug_info: string  := "false";
        cal_clk_sel     : string  := "pm_aux_iqclk_cal_clk_sel_cal_clk";
        cal_result_status: string  := "pm_aux_result_status_tx";
        continuous_calibration: string  := "false";
        pm_aux_cal_clk_test_sel: string  := "false";
        rx_cal_override_value: integer := 0;
        rx_cal_override_value_enable: string  := "false";
        rx_imp          : string  := "cal_imp_46_ohm";
        test_counter_enable: string  := "false";
        tx_cal_override_value: integer := 0;
        tx_cal_override_value_enable: string  := "false";
        tx_imp          : string  := "cal_imp_48_ohm";
        avmm_group_channel_index: integer := 0;
        use_default_base_address: string  := "true";
        user_base_address: integer := 0
    );
    port(
        atb0out         : inout  vl_logic_vector(0 downto 0);
        atb1out         : inout  vl_logic_vector(0 downto 0);
        calclk          : in     vl_logic_vector(0 downto 0);
        calpdb          : in     vl_logic_vector(0 downto 0);
        refiqclk        : in     vl_logic_vector(5 downto 0);
        testcntl        : in     vl_logic_vector(0 downto 0);
        nonusertoio     : out    vl_logic_vector(0 downto 0);
        zrxtx50         : out    vl_logic_vector(4 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of enable_debug_info : constant is 1;
    attribute mti_svvh_generic_type of cal_clk_sel : constant is 1;
    attribute mti_svvh_generic_type of cal_result_status : constant is 1;
    attribute mti_svvh_generic_type of continuous_calibration : constant is 1;
    attribute mti_svvh_generic_type of pm_aux_cal_clk_test_sel : constant is 1;
    attribute mti_svvh_generic_type of rx_cal_override_value : constant is 1;
    attribute mti_svvh_generic_type of rx_cal_override_value_enable : constant is 1;
    attribute mti_svvh_generic_type of rx_imp : constant is 1;
    attribute mti_svvh_generic_type of test_counter_enable : constant is 1;
    attribute mti_svvh_generic_type of tx_cal_override_value : constant is 1;
    attribute mti_svvh_generic_type of tx_cal_override_value_enable : constant is 1;
    attribute mti_svvh_generic_type of tx_imp : constant is 1;
    attribute mti_svvh_generic_type of avmm_group_channel_index : constant is 1;
    attribute mti_svvh_generic_type of use_default_base_address : constant is 1;
    attribute mti_svvh_generic_type of user_base_address : constant is 1;
end cyclonev_hssi_pma_aux;
