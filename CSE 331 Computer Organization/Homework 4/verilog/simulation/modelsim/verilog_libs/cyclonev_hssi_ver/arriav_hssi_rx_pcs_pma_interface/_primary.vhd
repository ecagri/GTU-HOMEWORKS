library verilog;
use verilog.vl_types.all;
entity arriav_hssi_rx_pcs_pma_interface is
    generic(
        enable_debug_info: string  := "false";
        selectpcs       : string  := "eight_g_pcs";
        clkslip_sel     : string  := "pld";
        prot_mode       : string  := "other_protocols";
        avmm_group_channel_index: integer := 0;
        use_default_base_address: string  := "true";
        user_base_address: integer := 0
    );
    port(
        pcs8grxclkiqout : in     vl_logic_vector(0 downto 0);
        pcs8grxclkslip  : in     vl_logic_vector(0 downto 0);
        pldrxclkslip    : in     vl_logic_vector(0 downto 0);
        pldrxpmarstb    : in     vl_logic_vector(0 downto 0);
        pmareservedin   : in     vl_logic_vector(4 downto 0);
        datainfrompma   : in     vl_logic_vector(79 downto 0);
        pmarxpllphaselockin: in     vl_logic_vector(0 downto 0);
        clockinfrompma  : in     vl_logic_vector(0 downto 0);
        pmasigdet       : in     vl_logic_vector(0 downto 0);
        dataoutto8gpcs  : out    vl_logic_vector(19 downto 0);
        clockoutto8gpcs : out    vl_logic_vector(0 downto 0);
        pcs8gsigdetni   : out    vl_logic_vector(0 downto 0);
        pmareservedout  : out    vl_logic_vector(4 downto 0);
        pmarxclkout     : out    vl_logic_vector(0 downto 0);
        pmarxpllphaselockout: out    vl_logic_vector(0 downto 0);
        pmarxclkslip    : out    vl_logic_vector(0 downto 0);
        pmarxpmarstb    : out    vl_logic_vector(0 downto 0);
        asynchdatain    : out    vl_logic_vector(0 downto 0);
        reset           : out    vl_logic_vector(0 downto 0);
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
    attribute mti_svvh_generic_type of selectpcs : constant is 1;
    attribute mti_svvh_generic_type of clkslip_sel : constant is 1;
    attribute mti_svvh_generic_type of prot_mode : constant is 1;
    attribute mti_svvh_generic_type of avmm_group_channel_index : constant is 1;
    attribute mti_svvh_generic_type of use_default_base_address : constant is 1;
    attribute mti_svvh_generic_type of user_base_address : constant is 1;
end arriav_hssi_rx_pcs_pma_interface;
