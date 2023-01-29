library verilog;
use verilog.vl_types.all;
entity cyclonev_crcblock is
    generic(
        oscillator_divider: integer := 256;
        error_delay     : integer := 0;
        error_dra_dl_bypass: string  := "false";
        crc_deld_disable: string  := "false";
        triple_adj_err_correction: string  := "false";
        quad_adj_err_correction: string  := "false";
        lpm_type        : string  := "cyclonev_crcblock"
    );
    port(
        clk             : in     vl_logic;
        shiftnld        : in     vl_logic;
        crcerror        : out    vl_logic;
        regout          : out    vl_logic;
        endofedfullchip : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of oscillator_divider : constant is 1;
    attribute mti_svvh_generic_type of error_delay : constant is 1;
    attribute mti_svvh_generic_type of error_dra_dl_bypass : constant is 1;
    attribute mti_svvh_generic_type of crc_deld_disable : constant is 1;
    attribute mti_svvh_generic_type of triple_adj_err_correction : constant is 1;
    attribute mti_svvh_generic_type of quad_adj_err_correction : constant is 1;
    attribute mti_svvh_generic_type of lpm_type : constant is 1;
end cyclonev_crcblock;
