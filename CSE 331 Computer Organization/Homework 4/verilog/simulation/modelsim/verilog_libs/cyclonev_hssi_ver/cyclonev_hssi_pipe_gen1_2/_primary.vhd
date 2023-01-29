library verilog;
use verilog.vl_types.all;
entity cyclonev_hssi_pipe_gen1_2 is
    generic(
        enable_debug_info: string  := "false";
        prot_mode       : string  := "pipe_g1";
        hip_mode        : string  := "dis_hip";
        tx_pipe_enable  : string  := "dis_pipe_tx";
        rx_pipe_enable  : string  := "dis_pipe_rx";
        pipe_byte_de_serializer_en: string  := "dont_care_bds";
        txswing         : string  := "dis_txswing";
        rxdetect_bypass : string  := "dis_rxdetect_bypass";
        error_replace_pad: string  := "replace_edb";
        ind_error_reporting: string  := "dis_ind_error_reporting";
        phystatus_rst_toggle: string  := "dis_phystatus_rst_toggle";
        elecidle_delay  : string  := "elec_idle_delay";
        elec_idle_delay_val: vl_logic_vector(2 downto 0) := (Hi0, Hi0, Hi0);
        phy_status_delay: string  := "phystatus_delay";
        phystatus_delay_val: vl_logic_vector(2 downto 0) := (Hi0, Hi0, Hi0);
        rvod_sel_d_val  : vl_logic_vector(5 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        rpre_emph_b_val : vl_logic_vector(5 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        rvod_sel_c_val  : vl_logic_vector(5 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        rpre_emph_c_val : vl_logic_vector(5 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        rpre_emph_settings: vl_logic_vector(5 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        rvod_sel_a_val  : vl_logic_vector(5 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        rpre_emph_d_val : vl_logic_vector(5 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        rvod_sel_settings: vl_logic_vector(5 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        rvod_sel_b_val  : vl_logic_vector(5 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        rpre_emph_e_val : vl_logic_vector(5 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        sup_mode        : string  := "user_mode";
        rvod_sel_e_val  : vl_logic_vector(5 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        rpre_emph_a_val : vl_logic_vector(5 downto 0) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        ctrl_plane_bonding_consumption: string  := "individual";
        avmm_group_channel_index: integer := 0;
        use_default_base_address: string  := "true";
        user_base_address: integer := 0
    );
    port(
        pcieswitch      : in     vl_logic_vector(0 downto 0);
        piperxclk       : in     vl_logic_vector(0 downto 0);
        pipetxclk       : in     vl_logic_vector(0 downto 0);
        polinvrx        : in     vl_logic_vector(0 downto 0);
        powerstatetransitiondone: in     vl_logic_vector(0 downto 0);
        powerstatetransitiondoneena: in     vl_logic_vector(0 downto 0);
        powerdown       : in     vl_logic_vector(1 downto 0);
        refclkb         : in     vl_logic_vector(0 downto 0);
        refclkbreset    : in     vl_logic_vector(0 downto 0);
        revloopbkpcsgen3: in     vl_logic_vector(0 downto 0);
        revloopback     : in     vl_logic_vector(0 downto 0);
        rxdetectvalid   : in     vl_logic_vector(0 downto 0);
        rxfound         : in     vl_logic_vector(0 downto 0);
        rxpipereset     : in     vl_logic_vector(0 downto 0);
        rxd             : in     vl_logic_vector(63 downto 0);
        rxelectricalidle: in     vl_logic_vector(0 downto 0);
        rxpolarity      : in     vl_logic_vector(0 downto 0);
        sigdetni        : in     vl_logic_vector(0 downto 0);
        speedchange     : in     vl_logic_vector(0 downto 0);
        speedchangechnldown: in     vl_logic_vector(0 downto 0);
        speedchangechnlup: in     vl_logic_vector(0 downto 0);
        txelecidlecomp  : in     vl_logic_vector(0 downto 0);
        txpipereset     : in     vl_logic_vector(0 downto 0);
        txdch           : in     vl_logic_vector(43 downto 0);
        txdeemph        : in     vl_logic_vector(0 downto 0);
        txdetectrxloopback: in     vl_logic_vector(0 downto 0);
        txelecidlein    : in     vl_logic_vector(0 downto 0);
        txmargin        : in     vl_logic_vector(2 downto 0);
        txswingport     : in     vl_logic_vector(0 downto 0);
        currentcoeff    : out    vl_logic_vector(17 downto 0);
        phystatus       : out    vl_logic_vector(0 downto 0);
        polinvrxint     : out    vl_logic_vector(0 downto 0);
        revloopbk       : out    vl_logic_vector(0 downto 0);
        rxdch           : out    vl_logic_vector(63 downto 0);
        rxelecidle      : out    vl_logic_vector(0 downto 0);
        rxelectricalidleout: out    vl_logic_vector(0 downto 0);
        rxstatus        : out    vl_logic_vector(2 downto 0);
        rxvalid         : out    vl_logic_vector(0 downto 0);
        speedchangeout  : out    vl_logic_vector(0 downto 0);
        txelecidleout   : out    vl_logic_vector(0 downto 0);
        txd             : out    vl_logic_vector(43 downto 0);
        txdetectrx      : out    vl_logic_vector(0 downto 0);
        avmmaddress     : in     vl_logic_vector(10 downto 0);
        avmmbyteen      : in     vl_logic_vector(1 downto 0);
        avmmclk         : in     vl_logic_vector(0 downto 0);
        avmmread        : in     vl_logic_vector(0 downto 0);
        avmmrstn        : in     vl_logic_vector(0 downto 0);
        avmmwrite       : in     vl_logic_vector(0 downto 0);
        avmmwritedata   : in     vl_logic_vector(15 downto 0);
        avmmreaddata    : out    vl_logic_vector(15 downto 0);
        blockselect     : out    vl_logic_vector(0 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of enable_debug_info : constant is 1;
    attribute mti_svvh_generic_type of prot_mode : constant is 1;
    attribute mti_svvh_generic_type of hip_mode : constant is 1;
    attribute mti_svvh_generic_type of tx_pipe_enable : constant is 1;
    attribute mti_svvh_generic_type of rx_pipe_enable : constant is 1;
    attribute mti_svvh_generic_type of pipe_byte_de_serializer_en : constant is 1;
    attribute mti_svvh_generic_type of txswing : constant is 1;
    attribute mti_svvh_generic_type of rxdetect_bypass : constant is 1;
    attribute mti_svvh_generic_type of error_replace_pad : constant is 1;
    attribute mti_svvh_generic_type of ind_error_reporting : constant is 1;
    attribute mti_svvh_generic_type of phystatus_rst_toggle : constant is 1;
    attribute mti_svvh_generic_type of elecidle_delay : constant is 1;
    attribute mti_svvh_generic_type of elec_idle_delay_val : constant is 2;
    attribute mti_svvh_generic_type of phy_status_delay : constant is 1;
    attribute mti_svvh_generic_type of phystatus_delay_val : constant is 2;
    attribute mti_svvh_generic_type of rvod_sel_d_val : constant is 2;
    attribute mti_svvh_generic_type of rpre_emph_b_val : constant is 2;
    attribute mti_svvh_generic_type of rvod_sel_c_val : constant is 2;
    attribute mti_svvh_generic_type of rpre_emph_c_val : constant is 2;
    attribute mti_svvh_generic_type of rpre_emph_settings : constant is 2;
    attribute mti_svvh_generic_type of rvod_sel_a_val : constant is 2;
    attribute mti_svvh_generic_type of rpre_emph_d_val : constant is 2;
    attribute mti_svvh_generic_type of rvod_sel_settings : constant is 2;
    attribute mti_svvh_generic_type of rvod_sel_b_val : constant is 2;
    attribute mti_svvh_generic_type of rpre_emph_e_val : constant is 2;
    attribute mti_svvh_generic_type of sup_mode : constant is 1;
    attribute mti_svvh_generic_type of rvod_sel_e_val : constant is 2;
    attribute mti_svvh_generic_type of rpre_emph_a_val : constant is 2;
    attribute mti_svvh_generic_type of ctrl_plane_bonding_consumption : constant is 1;
    attribute mti_svvh_generic_type of avmm_group_channel_index : constant is 1;
    attribute mti_svvh_generic_type of use_default_base_address : constant is 1;
    attribute mti_svvh_generic_type of user_base_address : constant is 1;
end cyclonev_hssi_pipe_gen1_2;
