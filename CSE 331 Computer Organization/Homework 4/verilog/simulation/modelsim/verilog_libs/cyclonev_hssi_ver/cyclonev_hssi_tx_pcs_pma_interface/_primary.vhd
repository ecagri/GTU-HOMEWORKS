library verilog;
use verilog.vl_types.all;
entity cyclonev_hssi_tx_pcs_pma_interface is
    generic(
        enable_debug_info: string  := "false";
        selectpcs       : string  := "eight_g_pcs";
        avmm_group_channel_index: integer := 0;
        use_default_base_address: string  := "true";
        user_base_address: integer := 0
    );
    port(
        datainfrom8gpcs : in     vl_logic_vector(19 downto 0);
        pcs8gtxclkiqout : in     vl_logic_vector(0 downto 0);
        pmarxfreqtxcmuplllockin: in     vl_logic_vector(0 downto 0);
        clockinfrompma  : in     vl_logic_vector(0 downto 0);
        clockoutto8gpcs : out    vl_logic_vector(0 downto 0);
        pmarxfreqtxcmuplllockout: out    vl_logic_vector(0 downto 0);
        pmatxclkout     : out    vl_logic_vector(0 downto 0);
        dataouttopma    : out    vl_logic_vector(79 downto 0);
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
    attribute mti_svvh_generic_type of avmm_group_channel_index : constant is 1;
    attribute mti_svvh_generic_type of use_default_base_address : constant is 1;
    attribute mti_svvh_generic_type of user_base_address : constant is 1;
end cyclonev_hssi_tx_pcs_pma_interface;
