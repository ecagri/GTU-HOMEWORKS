library verilog;
use verilog.vl_types.all;
entity arriav_hssi_pma_rx_deser is
    generic(
        enable_debug_info: string  := "false";
        auto_negotiation: string  := "false";
        channel_number  : integer := 0;
        clk_forward_only_mode: string  := "false";
        enable_bit_slip : string  := "true";
        mode            : integer := 8;
        sdclk_enable    : string  := "false";
        vco_bypass      : string  := "vco_bypass_normal";
        avmm_group_channel_index: integer := 0;
        use_default_base_address: string  := "true";
        user_base_address: integer := 0;
        pma_direct      : string  := "false"
    );
    port(
        bslip           : in     vl_logic_vector(0 downto 0);
        clk270b         : in     vl_logic_vector(0 downto 0);
        clk90b          : in     vl_logic_vector(0 downto 0);
        deven           : in     vl_logic_vector(0 downto 0);
        dodd            : in     vl_logic_vector(0 downto 0);
        pciesw          : in     vl_logic_vector(0 downto 0);
        rstn            : in     vl_logic_vector(0 downto 0);
        clkdivrx        : out    vl_logic_vector(0 downto 0);
        clkdivrxrx      : out    vl_logic_vector(0 downto 0);
        dout            : out    vl_logic_vector(79 downto 0);
        pciel           : out    vl_logic_vector(0 downto 0);
        avmmaddress     : in     vl_logic_vector(10 downto 0);
        avmmbyteen      : in     vl_logic_vector(1 downto 0);
        avmmrstn        : in     vl_logic_vector(0 downto 0);
        avmmclk         : in     vl_logic_vector(0 downto 0);
        avmmread        : in     vl_logic_vector(0 downto 0);
        avmmwrite       : in     vl_logic_vector(0 downto 0);
        avmmwritedata   : in     vl_logic_vector(15 downto 0);
        avmmreaddata    : out    vl_logic_vector(15 downto 0);
        blockselect     : out    vl_logic_vector(0 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of enable_debug_info : constant is 1;
    attribute mti_svvh_generic_type of auto_negotiation : constant is 1;
    attribute mti_svvh_generic_type of channel_number : constant is 1;
    attribute mti_svvh_generic_type of clk_forward_only_mode : constant is 1;
    attribute mti_svvh_generic_type of enable_bit_slip : constant is 1;
    attribute mti_svvh_generic_type of mode : constant is 1;
    attribute mti_svvh_generic_type of sdclk_enable : constant is 1;
    attribute mti_svvh_generic_type of vco_bypass : constant is 1;
    attribute mti_svvh_generic_type of avmm_group_channel_index : constant is 1;
    attribute mti_svvh_generic_type of use_default_base_address : constant is 1;
    attribute mti_svvh_generic_type of user_base_address : constant is 1;
    attribute mti_svvh_generic_type of pma_direct : constant is 1;
end arriav_hssi_pma_rx_deser;
