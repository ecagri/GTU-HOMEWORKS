library verilog;
use verilog.vl_types.all;
entity arriav_channel_pll is
    generic(
        sim_use_fast_model: string  := "true";
        enable_debug_info: string  := "false";
        cvp_en_iocsr    : string  := "false";
        avmm_group_channel_index: integer := 0;
        use_default_base_address: string  := "true";
        user_base_address: integer := 0;
        reference_clock_frequency: string  := "";
        output_clock_frequency: string  := "";
        enabled_for_reconfig: string  := "false";
        bbpd_salatch_offset_ctrl_clk0: string  := "offset_0mv";
        bbpd_salatch_offset_ctrl_clk180: string  := "offset_0mv";
        bbpd_salatch_offset_ctrl_clk270: string  := "offset_0mv";
        bbpd_salatch_offset_ctrl_clk90: string  := "offset_0mv";
        bbpd_salatch_sel: string  := "normal";
        bypass_cp_rgla  : string  := "false";
        cdr_atb_select  : string  := "atb_disable";
        cgb_clk_enable  : string  := "false";
        charge_pump_current_test: string  := "enable_ch_pump_normal";
        clklow_fref_to_ppm_div_sel: integer := 1;
        clock_monitor   : string  := "lpbk_data";
        diag_rev_lpbk   : string  := "false";
        enable_gpon_detection: string  := "false";
        fast_lock_mode  : string  := "true";
        fb_sel          : string  := "vcoclk";
        hs_levshift_power_supply_setting: integer := 1;
        ignore_phslock  : string  := "false";
        l_counter_pd_clock_disable: string  := "false";
        m_counter       : integer := -1;
        pcie_freq_control: string  := "pcie_100mhz";
        pd_charge_pump_current_ctrl: integer := 5;
        pd_l_counter    : integer := 1;
        pfd_charge_pump_current_ctrl: integer := 20;
        pfd_l_counter   : integer := 1;
        powerdown       : string  := "false";
        ref_clk_div     : integer := -1;
        regulator_volt_inc: string  := "0";
        replica_bias_ctrl: string  := "true";
        reverse_serial_lpbk: string  := "false";
        ripple_cap_ctrl : string  := "none";
        rxpll_pd_bw_ctrl: integer := 300;
        rxpll_pfd_bw_ctrl: integer := 3200;
        txpll_hclk_driver_enable: string  := "false";
        vco_overange_ref: string  := "ref_2";
        vco_range_ctrl_en: string  := "true"
    );
    port(
        avmmaddress     : in     vl_logic_vector(10 downto 0);
        avmmbyteen      : in     vl_logic_vector(1 downto 0);
        avmmclk         : in     vl_logic_vector(0 downto 0);
        avmmread        : in     vl_logic_vector(0 downto 0);
        avmmrstn        : in     vl_logic_vector(0 downto 0);
        avmmwrite       : in     vl_logic_vector(0 downto 0);
        avmmwritedata   : in     vl_logic_vector(15 downto 0);
        avmmreaddata    : out    vl_logic_vector(15 downto 0);
        blockselect     : out    vl_logic_vector(0 downto 0);
        clkindeser      : in     vl_logic_vector(0 downto 0);
        crurstb         : in     vl_logic_vector(0 downto 0);
        earlyeios       : in     vl_logic_vector(0 downto 0);
        extclk          : in     vl_logic_vector(0 downto 0);
        lpbkpreen       : in     vl_logic_vector(0 downto 0);
        ltd             : in     vl_logic_vector(0 downto 0);
        ltr             : in     vl_logic_vector(0 downto 0);
        occalen         : in     vl_logic_vector(0 downto 0);
        pciel           : in     vl_logic_vector(0 downto 0);
        pciesw          : in     vl_logic_vector(1 downto 0);
        ppmlock         : in     vl_logic_vector(0 downto 0);
        refclk          : in     vl_logic_vector(0 downto 0);
        rstn            : in     vl_logic_vector(0 downto 0);
        rxp             : in     vl_logic_vector(0 downto 0);
        sd              : in     vl_logic_vector(0 downto 0);
        ck0pd           : out    vl_logic_vector(0 downto 0);
        ck180pd         : out    vl_logic_vector(0 downto 0);
        ck270pd         : out    vl_logic_vector(0 downto 0);
        ck90pd          : out    vl_logic_vector(0 downto 0);
        clk270bdes      : out    vl_logic_vector(0 downto 0);
        clk90bdes       : out    vl_logic_vector(0 downto 0);
        clkcdr          : out    vl_logic_vector(0 downto 0);
        clklow          : out    vl_logic_vector(0 downto 0);
        deven           : out    vl_logic_vector(0 downto 0);
        dodd            : out    vl_logic_vector(0 downto 0);
        fref            : out    vl_logic_vector(0 downto 0);
        pdof            : out    vl_logic_vector(3 downto 0);
        pfdmodelock     : out    vl_logic_vector(0 downto 0);
        rxlpbdp         : out    vl_logic_vector(0 downto 0);
        rxlpbp          : out    vl_logic_vector(0 downto 0);
        rxplllock       : out    vl_logic_vector(0 downto 0);
        txpllhclk       : out    vl_logic_vector(0 downto 0);
        txrlpbk         : out    vl_logic_vector(0 downto 0);
        vctrloverrange  : out    vl_logic_vector(0 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of sim_use_fast_model : constant is 1;
    attribute mti_svvh_generic_type of enable_debug_info : constant is 1;
    attribute mti_svvh_generic_type of cvp_en_iocsr : constant is 1;
    attribute mti_svvh_generic_type of avmm_group_channel_index : constant is 1;
    attribute mti_svvh_generic_type of use_default_base_address : constant is 1;
    attribute mti_svvh_generic_type of user_base_address : constant is 1;
    attribute mti_svvh_generic_type of reference_clock_frequency : constant is 1;
    attribute mti_svvh_generic_type of output_clock_frequency : constant is 1;
    attribute mti_svvh_generic_type of enabled_for_reconfig : constant is 1;
    attribute mti_svvh_generic_type of bbpd_salatch_offset_ctrl_clk0 : constant is 1;
    attribute mti_svvh_generic_type of bbpd_salatch_offset_ctrl_clk180 : constant is 1;
    attribute mti_svvh_generic_type of bbpd_salatch_offset_ctrl_clk270 : constant is 1;
    attribute mti_svvh_generic_type of bbpd_salatch_offset_ctrl_clk90 : constant is 1;
    attribute mti_svvh_generic_type of bbpd_salatch_sel : constant is 1;
    attribute mti_svvh_generic_type of bypass_cp_rgla : constant is 1;
    attribute mti_svvh_generic_type of cdr_atb_select : constant is 1;
    attribute mti_svvh_generic_type of cgb_clk_enable : constant is 1;
    attribute mti_svvh_generic_type of charge_pump_current_test : constant is 1;
    attribute mti_svvh_generic_type of clklow_fref_to_ppm_div_sel : constant is 1;
    attribute mti_svvh_generic_type of clock_monitor : constant is 1;
    attribute mti_svvh_generic_type of diag_rev_lpbk : constant is 1;
    attribute mti_svvh_generic_type of enable_gpon_detection : constant is 1;
    attribute mti_svvh_generic_type of fast_lock_mode : constant is 1;
    attribute mti_svvh_generic_type of fb_sel : constant is 1;
    attribute mti_svvh_generic_type of hs_levshift_power_supply_setting : constant is 1;
    attribute mti_svvh_generic_type of ignore_phslock : constant is 1;
    attribute mti_svvh_generic_type of l_counter_pd_clock_disable : constant is 1;
    attribute mti_svvh_generic_type of m_counter : constant is 1;
    attribute mti_svvh_generic_type of pcie_freq_control : constant is 1;
    attribute mti_svvh_generic_type of pd_charge_pump_current_ctrl : constant is 1;
    attribute mti_svvh_generic_type of pd_l_counter : constant is 1;
    attribute mti_svvh_generic_type of pfd_charge_pump_current_ctrl : constant is 1;
    attribute mti_svvh_generic_type of pfd_l_counter : constant is 1;
    attribute mti_svvh_generic_type of powerdown : constant is 1;
    attribute mti_svvh_generic_type of ref_clk_div : constant is 1;
    attribute mti_svvh_generic_type of regulator_volt_inc : constant is 1;
    attribute mti_svvh_generic_type of replica_bias_ctrl : constant is 1;
    attribute mti_svvh_generic_type of reverse_serial_lpbk : constant is 1;
    attribute mti_svvh_generic_type of ripple_cap_ctrl : constant is 1;
    attribute mti_svvh_generic_type of rxpll_pd_bw_ctrl : constant is 1;
    attribute mti_svvh_generic_type of rxpll_pfd_bw_ctrl : constant is 1;
    attribute mti_svvh_generic_type of txpll_hclk_driver_enable : constant is 1;
    attribute mti_svvh_generic_type of vco_overange_ref : constant is 1;
    attribute mti_svvh_generic_type of vco_range_ctrl_en : constant is 1;
end arriav_channel_pll;
