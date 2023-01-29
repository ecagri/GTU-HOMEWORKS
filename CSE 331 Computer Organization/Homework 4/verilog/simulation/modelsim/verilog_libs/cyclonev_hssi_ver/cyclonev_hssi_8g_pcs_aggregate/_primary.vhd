library verilog;
use verilog.vl_types.all;
entity cyclonev_hssi_8g_pcs_aggregate is
    generic(
        enable_debug_info: string  := "false";
        xaui_sm_operation: string  := "en_xaui_sm";
        dskw_sm_operation: string  := "dskw_xaui_sm";
        data_agg_bonding: string  := "agg_disable";
        prot_mode_tx    : string  := "pipe_g1_tx";
        pcs_dw_datapath : string  := "sw_data_path";
        dskw_control    : string  := "dskw_write_control";
        refclkdig_sel   : string  := "dis_refclk_dig_sel";
        agg_pwdn        : string  := "dis_agg_pwdn";
        dskw_mnumber_data: vl_logic_vector(3 downto 0) := (Hi0, Hi1, Hi0, Hi0);
        avmm_group_channel_index: integer := 0;
        use_default_base_address: string  := "true";
        user_base_address: integer := 0
    );
    port(
        aligndetsyncbotch2: in     vl_logic_vector(1 downto 0);
        aligndetsyncch0 : in     vl_logic_vector(1 downto 0);
        aligndetsyncch1 : in     vl_logic_vector(1 downto 0);
        aligndetsyncch2 : in     vl_logic_vector(1 downto 0);
        aligndetsynctopch0: in     vl_logic_vector(1 downto 0);
        aligndetsynctopch1: in     vl_logic_vector(1 downto 0);
        alignstatussyncbotch2: in     vl_logic_vector(0 downto 0);
        alignstatussyncch0: in     vl_logic_vector(0 downto 0);
        alignstatussyncch1: in     vl_logic_vector(0 downto 0);
        alignstatussyncch2: in     vl_logic_vector(0 downto 0);
        alignstatussynctopch0: in     vl_logic_vector(0 downto 0);
        alignstatussynctopch1: in     vl_logic_vector(0 downto 0);
        cgcomprddinbotch2: in     vl_logic_vector(1 downto 0);
        cgcomprddinch0  : in     vl_logic_vector(1 downto 0);
        cgcomprddinch1  : in     vl_logic_vector(1 downto 0);
        cgcomprddinch2  : in     vl_logic_vector(1 downto 0);
        cgcomprddintopch0: in     vl_logic_vector(1 downto 0);
        cgcomprddintopch1: in     vl_logic_vector(1 downto 0);
        cgcompwrinbotch2: in     vl_logic_vector(1 downto 0);
        cgcompwrinch0   : in     vl_logic_vector(1 downto 0);
        cgcompwrinch1   : in     vl_logic_vector(1 downto 0);
        cgcompwrinch2   : in     vl_logic_vector(1 downto 0);
        cgcompwrintopch0: in     vl_logic_vector(1 downto 0);
        cgcompwrintopch1: in     vl_logic_vector(1 downto 0);
        decctlbotch2    : in     vl_logic_vector(0 downto 0);
        decctlch0       : in     vl_logic_vector(0 downto 0);
        decctlch1       : in     vl_logic_vector(0 downto 0);
        decctlch2       : in     vl_logic_vector(0 downto 0);
        decctltopch0    : in     vl_logic_vector(0 downto 0);
        decctltopch1    : in     vl_logic_vector(0 downto 0);
        decdatabotch2   : in     vl_logic_vector(7 downto 0);
        decdatach0      : in     vl_logic_vector(7 downto 0);
        decdatach1      : in     vl_logic_vector(7 downto 0);
        decdatach2      : in     vl_logic_vector(7 downto 0);
        decdatatopch0   : in     vl_logic_vector(7 downto 0);
        decdatatopch1   : in     vl_logic_vector(7 downto 0);
        decdatavalidbotch2: in     vl_logic_vector(0 downto 0);
        decdatavalidch0 : in     vl_logic_vector(0 downto 0);
        decdatavalidch1 : in     vl_logic_vector(0 downto 0);
        decdatavalidch2 : in     vl_logic_vector(0 downto 0);
        decdatavalidtopch0: in     vl_logic_vector(0 downto 0);
        decdatavalidtopch1: in     vl_logic_vector(0 downto 0);
        dedicatedaggscaninch1: in     vl_logic_vector(0 downto 0);
        delcondmetinbotch2: in     vl_logic_vector(0 downto 0);
        delcondmetinch0 : in     vl_logic_vector(0 downto 0);
        delcondmetinch1 : in     vl_logic_vector(0 downto 0);
        delcondmetinch2 : in     vl_logic_vector(0 downto 0);
        delcondmetintopch0: in     vl_logic_vector(0 downto 0);
        delcondmetintopch1: in     vl_logic_vector(0 downto 0);
        dprioagg        : in     vl_logic_vector(63 downto 0);
        fifoovrinbotch2 : in     vl_logic_vector(0 downto 0);
        fifoovrinch0    : in     vl_logic_vector(0 downto 0);
        fifoovrinch1    : in     vl_logic_vector(0 downto 0);
        fifoovrinch2    : in     vl_logic_vector(0 downto 0);
        fifoovrintopch0 : in     vl_logic_vector(0 downto 0);
        fifoovrintopch1 : in     vl_logic_vector(0 downto 0);
        fifordinbotch2  : in     vl_logic_vector(0 downto 0);
        fifordinch0     : in     vl_logic_vector(0 downto 0);
        fifordinch1     : in     vl_logic_vector(0 downto 0);
        fifordinch2     : in     vl_logic_vector(0 downto 0);
        fifordintopch0  : in     vl_logic_vector(0 downto 0);
        fifordintopch1  : in     vl_logic_vector(0 downto 0);
        insertincompleteinbotch2: in     vl_logic_vector(0 downto 0);
        insertincompleteinch0: in     vl_logic_vector(0 downto 0);
        insertincompleteinch1: in     vl_logic_vector(0 downto 0);
        insertincompleteinch2: in     vl_logic_vector(0 downto 0);
        insertincompleteintopch0: in     vl_logic_vector(0 downto 0);
        insertincompleteintopch1: in     vl_logic_vector(0 downto 0);
        latencycompinbotch2: in     vl_logic_vector(0 downto 0);
        latencycompinch0: in     vl_logic_vector(0 downto 0);
        latencycompinch1: in     vl_logic_vector(0 downto 0);
        latencycompinch2: in     vl_logic_vector(0 downto 0);
        latencycompintopch0: in     vl_logic_vector(0 downto 0);
        latencycompintopch1: in     vl_logic_vector(0 downto 0);
        rcvdclkch0      : in     vl_logic_vector(0 downto 0);
        rcvdclkch1      : in     vl_logic_vector(0 downto 0);
        rdalignbotch2   : in     vl_logic_vector(1 downto 0);
        rdalignch0      : in     vl_logic_vector(1 downto 0);
        rdalignch1      : in     vl_logic_vector(1 downto 0);
        rdalignch2      : in     vl_logic_vector(1 downto 0);
        rdaligntopch0   : in     vl_logic_vector(1 downto 0);
        rdaligntopch1   : in     vl_logic_vector(1 downto 0);
        rdenablesyncbotch2: in     vl_logic_vector(0 downto 0);
        rdenablesyncch0 : in     vl_logic_vector(0 downto 0);
        rdenablesyncch1 : in     vl_logic_vector(0 downto 0);
        rdenablesyncch2 : in     vl_logic_vector(0 downto 0);
        rdenablesynctopch0: in     vl_logic_vector(0 downto 0);
        rdenablesynctopch1: in     vl_logic_vector(0 downto 0);
        refclkdig       : in     vl_logic_vector(0 downto 0);
        runningdispbotch2: in     vl_logic_vector(1 downto 0);
        runningdispch0  : in     vl_logic_vector(1 downto 0);
        runningdispch1  : in     vl_logic_vector(1 downto 0);
        runningdispch2  : in     vl_logic_vector(1 downto 0);
        runningdisptopch0: in     vl_logic_vector(1 downto 0);
        runningdisptopch1: in     vl_logic_vector(1 downto 0);
        rxpcsrstn       : in     vl_logic_vector(0 downto 0);
        scanmoden       : in     vl_logic_vector(0 downto 0);
        scanshiftn      : in     vl_logic_vector(0 downto 0);
        syncstatusbotch2: in     vl_logic_vector(0 downto 0);
        syncstatusch0   : in     vl_logic_vector(0 downto 0);
        syncstatusch1   : in     vl_logic_vector(0 downto 0);
        syncstatusch2   : in     vl_logic_vector(0 downto 0);
        syncstatustopch0: in     vl_logic_vector(0 downto 0);
        syncstatustopch1: in     vl_logic_vector(0 downto 0);
        txctltcbotch2   : in     vl_logic_vector(0 downto 0);
        txctltcch0      : in     vl_logic_vector(0 downto 0);
        txctltcch1      : in     vl_logic_vector(0 downto 0);
        txctltcch2      : in     vl_logic_vector(0 downto 0);
        txctltctopch0   : in     vl_logic_vector(0 downto 0);
        txctltctopch1   : in     vl_logic_vector(0 downto 0);
        txdatatcbotch2  : in     vl_logic_vector(7 downto 0);
        txdatatcch0     : in     vl_logic_vector(7 downto 0);
        txdatatcch1     : in     vl_logic_vector(7 downto 0);
        txdatatcch2     : in     vl_logic_vector(7 downto 0);
        txdatatctopch0  : in     vl_logic_vector(7 downto 0);
        txdatatctopch1  : in     vl_logic_vector(7 downto 0);
        txpcsrstn       : in     vl_logic_vector(0 downto 0);
        txpmaclk        : in     vl_logic_vector(0 downto 0);
        aggtestbusch0   : out    vl_logic_vector(15 downto 0);
        aggtestbusch1   : out    vl_logic_vector(15 downto 0);
        aggtestbusch2   : out    vl_logic_vector(15 downto 0);
        alignstatusbotch2: out    vl_logic_vector(0 downto 0);
        alignstatusch0  : out    vl_logic_vector(0 downto 0);
        alignstatusch1  : out    vl_logic_vector(0 downto 0);
        alignstatusch2  : out    vl_logic_vector(0 downto 0);
        alignstatussync0botch2: out    vl_logic_vector(0 downto 0);
        alignstatussync0ch0: out    vl_logic_vector(0 downto 0);
        alignstatussync0ch1: out    vl_logic_vector(0 downto 0);
        alignstatussync0ch2: out    vl_logic_vector(0 downto 0);
        alignstatussync0topch0: out    vl_logic_vector(0 downto 0);
        alignstatussync0topch1: out    vl_logic_vector(0 downto 0);
        alignstatustopch0: out    vl_logic_vector(0 downto 0);
        alignstatustopch1: out    vl_logic_vector(0 downto 0);
        cgcomprddallbotch2: out    vl_logic_vector(0 downto 0);
        cgcomprddallch0 : out    vl_logic_vector(0 downto 0);
        cgcomprddallch1 : out    vl_logic_vector(0 downto 0);
        cgcomprddallch2 : out    vl_logic_vector(0 downto 0);
        cgcomprddalltopch0: out    vl_logic_vector(0 downto 0);
        cgcomprddalltopch1: out    vl_logic_vector(0 downto 0);
        cgcompwrallbotch2: out    vl_logic_vector(0 downto 0);
        cgcompwrallch0  : out    vl_logic_vector(0 downto 0);
        cgcompwrallch1  : out    vl_logic_vector(0 downto 0);
        cgcompwrallch2  : out    vl_logic_vector(0 downto 0);
        cgcompwralltopch0: out    vl_logic_vector(0 downto 0);
        cgcompwralltopch1: out    vl_logic_vector(0 downto 0);
        dedicatedaggscanoutch0tieoff: out    vl_logic_vector(0 downto 0);
        dedicatedaggscanoutch1: out    vl_logic_vector(0 downto 0);
        dedicatedaggscanoutch2tieoff: out    vl_logic_vector(0 downto 0);
        delcondmet0botch2: out    vl_logic_vector(0 downto 0);
        delcondmet0ch0  : out    vl_logic_vector(0 downto 0);
        delcondmet0ch1  : out    vl_logic_vector(0 downto 0);
        delcondmet0ch2  : out    vl_logic_vector(0 downto 0);
        delcondmet0topch0: out    vl_logic_vector(0 downto 0);
        delcondmet0topch1: out    vl_logic_vector(0 downto 0);
        endskwqdbotch2  : out    vl_logic_vector(0 downto 0);
        endskwqdch0     : out    vl_logic_vector(0 downto 0);
        endskwqdch1     : out    vl_logic_vector(0 downto 0);
        endskwqdch2     : out    vl_logic_vector(0 downto 0);
        endskwqdtopch0  : out    vl_logic_vector(0 downto 0);
        endskwqdtopch1  : out    vl_logic_vector(0 downto 0);
        endskwrdptrsbotch2: out    vl_logic_vector(0 downto 0);
        endskwrdptrsch0 : out    vl_logic_vector(0 downto 0);
        endskwrdptrsch1 : out    vl_logic_vector(0 downto 0);
        endskwrdptrsch2 : out    vl_logic_vector(0 downto 0);
        endskwrdptrstopch0: out    vl_logic_vector(0 downto 0);
        endskwrdptrstopch1: out    vl_logic_vector(0 downto 0);
        fifoovr0botch2  : out    vl_logic_vector(0 downto 0);
        fifoovr0ch0     : out    vl_logic_vector(0 downto 0);
        fifoovr0ch1     : out    vl_logic_vector(0 downto 0);
        fifoovr0ch2     : out    vl_logic_vector(0 downto 0);
        fifoovr0topch0  : out    vl_logic_vector(0 downto 0);
        fifoovr0topch1  : out    vl_logic_vector(0 downto 0);
        fifordoutcomp0botch2: out    vl_logic_vector(0 downto 0);
        fifordoutcomp0ch0: out    vl_logic_vector(0 downto 0);
        fifordoutcomp0ch1: out    vl_logic_vector(0 downto 0);
        fifordoutcomp0ch2: out    vl_logic_vector(0 downto 0);
        fifordoutcomp0topch0: out    vl_logic_vector(0 downto 0);
        fifordoutcomp0topch1: out    vl_logic_vector(0 downto 0);
        fiforstrdqdbotch2: out    vl_logic_vector(0 downto 0);
        fiforstrdqdch0  : out    vl_logic_vector(0 downto 0);
        fiforstrdqdch1  : out    vl_logic_vector(0 downto 0);
        fiforstrdqdch2  : out    vl_logic_vector(0 downto 0);
        fiforstrdqdtopch0: out    vl_logic_vector(0 downto 0);
        fiforstrdqdtopch1: out    vl_logic_vector(0 downto 0);
        insertincomplete0botch2: out    vl_logic_vector(0 downto 0);
        insertincomplete0ch0: out    vl_logic_vector(0 downto 0);
        insertincomplete0ch1: out    vl_logic_vector(0 downto 0);
        insertincomplete0ch2: out    vl_logic_vector(0 downto 0);
        insertincomplete0topch0: out    vl_logic_vector(0 downto 0);
        insertincomplete0topch1: out    vl_logic_vector(0 downto 0);
        latencycomp0botch2: out    vl_logic_vector(0 downto 0);
        latencycomp0ch0 : out    vl_logic_vector(0 downto 0);
        latencycomp0ch1 : out    vl_logic_vector(0 downto 0);
        latencycomp0ch2 : out    vl_logic_vector(0 downto 0);
        latencycomp0topch0: out    vl_logic_vector(0 downto 0);
        latencycomp0topch1: out    vl_logic_vector(0 downto 0);
        rcvdclkout      : out    vl_logic_vector(0 downto 0);
        rcvdclkoutbot   : out    vl_logic_vector(0 downto 0);
        rcvdclkouttop   : out    vl_logic_vector(0 downto 0);
        rxctlrsbotch2   : out    vl_logic_vector(0 downto 0);
        rxctlrsch0      : out    vl_logic_vector(0 downto 0);
        rxctlrsch1      : out    vl_logic_vector(0 downto 0);
        rxctlrsch2      : out    vl_logic_vector(0 downto 0);
        rxctlrstopch0   : out    vl_logic_vector(0 downto 0);
        rxctlrstopch1   : out    vl_logic_vector(0 downto 0);
        rxdatarsbotch2  : out    vl_logic_vector(7 downto 0);
        rxdatarsch0     : out    vl_logic_vector(7 downto 0);
        rxdatarsch1     : out    vl_logic_vector(7 downto 0);
        rxdatarsch2     : out    vl_logic_vector(7 downto 0);
        rxdatarstopch0  : out    vl_logic_vector(7 downto 0);
        rxdatarstopch1  : out    vl_logic_vector(7 downto 0);
        txctltsbotch2   : out    vl_logic_vector(0 downto 0);
        txctltsch0      : out    vl_logic_vector(0 downto 0);
        txctltsch1      : out    vl_logic_vector(0 downto 0);
        txctltsch2      : out    vl_logic_vector(0 downto 0);
        txctltstopch0   : out    vl_logic_vector(0 downto 0);
        txctltstopch1   : out    vl_logic_vector(0 downto 0);
        txdatatsbotch2  : out    vl_logic_vector(7 downto 0);
        txdatatsch0     : out    vl_logic_vector(7 downto 0);
        txdatatsch1     : out    vl_logic_vector(7 downto 0);
        txdatatsch2     : out    vl_logic_vector(7 downto 0);
        txdatatstopch0  : out    vl_logic_vector(7 downto 0);
        txdatatstopch1  : out    vl_logic_vector(7 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of enable_debug_info : constant is 1;
    attribute mti_svvh_generic_type of xaui_sm_operation : constant is 1;
    attribute mti_svvh_generic_type of dskw_sm_operation : constant is 1;
    attribute mti_svvh_generic_type of data_agg_bonding : constant is 1;
    attribute mti_svvh_generic_type of prot_mode_tx : constant is 1;
    attribute mti_svvh_generic_type of pcs_dw_datapath : constant is 1;
    attribute mti_svvh_generic_type of dskw_control : constant is 1;
    attribute mti_svvh_generic_type of refclkdig_sel : constant is 1;
    attribute mti_svvh_generic_type of agg_pwdn : constant is 1;
    attribute mti_svvh_generic_type of dskw_mnumber_data : constant is 2;
    attribute mti_svvh_generic_type of avmm_group_channel_index : constant is 1;
    attribute mti_svvh_generic_type of use_default_base_address : constant is 1;
    attribute mti_svvh_generic_type of user_base_address : constant is 1;
end cyclonev_hssi_8g_pcs_aggregate;
