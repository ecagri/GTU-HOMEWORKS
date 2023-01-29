library verilog;
use verilog.vl_types.all;
entity cyclonev_prblock is
    generic(
        lpm_type        : string  := "cyclonev_prblock"
    );
    port(
        clk             : in     vl_logic;
        corectl         : in     vl_logic;
        prrequest       : in     vl_logic;
        data            : in     vl_logic_vector(15 downto 0);
        externalrequest : out    vl_logic;
        error           : out    vl_logic;
        ready           : out    vl_logic;
        done            : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of lpm_type : constant is 1;
end cyclonev_prblock;
