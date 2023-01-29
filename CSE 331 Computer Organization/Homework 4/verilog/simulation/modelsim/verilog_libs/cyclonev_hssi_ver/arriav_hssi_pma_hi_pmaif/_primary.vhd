library verilog;
use verilog.vl_types.all;
entity arriav_hssi_pma_hi_pmaif is
    generic(
        lpm_type        : string  := "arriav_hssi_pma_hi_pmaif";
        tx_pma_direction_sel: string  := "pcs"
    );
    port(
        datainfromcore  : in     vl_logic_vector(79 downto 0);
        datainfrompcs   : in     vl_logic_vector(79 downto 0);
        dataouttopma    : out    vl_logic_vector(79 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of lpm_type : constant is 1;
    attribute mti_svvh_generic_type of tx_pma_direction_sel : constant is 1;
end arriav_hssi_pma_hi_pmaif;
