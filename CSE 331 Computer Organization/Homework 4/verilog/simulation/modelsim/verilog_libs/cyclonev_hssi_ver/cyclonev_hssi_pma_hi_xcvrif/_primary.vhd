library verilog;
use verilog.vl_types.all;
entity cyclonev_hssi_pma_hi_xcvrif is
    generic(
        lpm_type        : string  := "cyclonev_hssi_pma_hi_xcvrif";
        rx_pma_direction_sel: string  := "pcs"
    );
    port(
        datainfrompma   : in     vl_logic_vector(79 downto 0);
        datainfrompcs   : in     vl_logic_vector(79 downto 0);
        dataouttopld    : out    vl_logic_vector(79 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of lpm_type : constant is 1;
    attribute mti_svvh_generic_type of rx_pma_direction_sel : constant is 1;
end cyclonev_hssi_pma_hi_xcvrif;
