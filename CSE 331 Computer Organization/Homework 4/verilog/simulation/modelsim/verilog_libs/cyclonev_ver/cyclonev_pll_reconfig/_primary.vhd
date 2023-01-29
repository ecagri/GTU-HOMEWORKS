library verilog;
use verilog.vl_types.all;
entity cyclonev_pll_reconfig is
    generic(
        fractional_pll_index: integer := 1
    );
    port(
        addr            : in     vl_logic_vector(5 downto 0);
        atpgmode        : in     vl_logic_vector(0 downto 0);
        byteen          : in     vl_logic_vector(1 downto 0);
        clk             : in     vl_logic_vector(0 downto 0);
        cntnen          : in     vl_logic_vector(0 downto 0);
        cntsel          : in     vl_logic_vector(4 downto 0);
        din             : in     vl_logic_vector(15 downto 0);
        fpllcsrtest     : in     vl_logic_vector(0 downto 0);
        iocsrclkin      : in     vl_logic_vector(0 downto 0);
        iocsrdatain     : in     vl_logic_vector(0 downto 0);
        iocsren         : in     vl_logic_vector(0 downto 0);
        iocsrrstn       : in     vl_logic_vector(0 downto 0);
        mdiodis         : in     vl_logic_vector(0 downto 0);
        mhi             : in     vl_logic_vector(7 downto 0);
        phaseen         : in     vl_logic_vector(0 downto 0);
        read            : in     vl_logic_vector(0 downto 0);
        rstn            : in     vl_logic_vector(0 downto 0);
        scanen          : in     vl_logic_vector(0 downto 0);
        sershiftload    : in     vl_logic_vector(0 downto 0);
        shiftdonei      : in     vl_logic_vector(0 downto 0);
        updn            : in     vl_logic_vector(0 downto 0);
        write           : in     vl_logic_vector(0 downto 0);
        blockselect     : out    vl_logic_vector(0 downto 0);
        dout            : out    vl_logic_vector(15 downto 0);
        dprioout        : out    vl_logic_vector(815 downto 0);
        iocsrdataout    : out    vl_logic_vector(0 downto 0);
        iocsrenbuf      : out    vl_logic_vector(0 downto 0);
        iocsrrstnbuf    : out    vl_logic_vector(0 downto 0);
        phasedone       : out    vl_logic_vector(0 downto 0);
        shift           : out    vl_logic_vector(0 downto 0);
        shiften         : out    vl_logic_vector(8 downto 0);
        shiftenm        : out    vl_logic_vector(0 downto 0);
        up              : out    vl_logic_vector(0 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of fractional_pll_index : constant is 1;
end cyclonev_pll_reconfig;
