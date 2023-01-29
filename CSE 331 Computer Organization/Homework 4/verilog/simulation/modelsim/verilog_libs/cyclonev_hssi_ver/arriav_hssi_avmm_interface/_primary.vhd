library verilog;
use verilog.vl_types.all;
entity arriav_hssi_avmm_interface is
    generic(
        num_ch0_atoms   : integer := 0;
        num_ch1_atoms   : integer := 0;
        num_ch2_atoms   : integer := 0
    );
    port(
        avmmrstn        : in     vl_logic;
        avmmclk         : in     vl_logic;
        avmmwrite       : in     vl_logic;
        avmmread        : in     vl_logic;
        avmmbyteen      : in     vl_logic_vector(1 downto 0);
        avmmaddress     : in     vl_logic_vector(10 downto 0);
        avmmwritedata   : in     vl_logic_vector(15 downto 0);
        blockselect     : in     vl_logic_vector(89 downto 0);
        readdatachnl    : in     vl_logic_vector(1439 downto 0);
        avmmreaddata    : out    vl_logic_vector(15 downto 0);
        clkchnl         : out    vl_logic;
        rstnchnl        : out    vl_logic;
        writedatachnl   : out    vl_logic_vector(15 downto 0);
        regaddrchnl     : out    vl_logic_vector(10 downto 0);
        writechnl       : out    vl_logic;
        readchnl        : out    vl_logic;
        byteenchnl      : out    vl_logic_vector(1 downto 0);
        refclkdig       : in     vl_logic;
        avmmreservedin  : in     vl_logic;
        avmmreservedout : out    vl_logic;
        dpriorstntop    : out    vl_logic;
        dprioclktop     : out    vl_logic;
        mdiodistopchnl  : out    vl_logic;
        dpriorstnmid    : out    vl_logic;
        dprioclkmid     : out    vl_logic;
        mdiodismidchnl  : out    vl_logic;
        dpriorstnbot    : out    vl_logic;
        dprioclkbot     : out    vl_logic;
        mdiodisbotchnl  : out    vl_logic;
        dpriotestsitopchnl: out    vl_logic_vector(3 downto 0);
        dpriotestsimidchnl: out    vl_logic_vector(3 downto 0);
        dpriotestsibotchnl: out    vl_logic_vector(3 downto 0);
        pmatestbussel   : in     vl_logic_vector(11 downto 0);
        pmatestbus      : out    vl_logic_vector(23 downto 0);
        scanmoden       : in     vl_logic;
        scanshiftn      : in     vl_logic;
        interfacesel    : in     vl_logic;
        sershiftload    : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of num_ch0_atoms : constant is 1;
    attribute mti_svvh_generic_type of num_ch1_atoms : constant is 1;
    attribute mti_svvh_generic_type of num_ch2_atoms : constant is 1;
end arriav_hssi_avmm_interface;
