library verilog;
use verilog.vl_types.all;
entity cypherDetector is
    port(
        cypher          : in     vl_logic_vector(15 downto 0);
        data            : in     vl_logic_vector(3 downto 0);
        read            : in     vl_logic;
        reset           : in     vl_logic;
        clock           : in     vl_logic;
        collected       : out    vl_logic;
        sum             : out    vl_logic_vector(7 downto 0)
    );
end cypherDetector;
