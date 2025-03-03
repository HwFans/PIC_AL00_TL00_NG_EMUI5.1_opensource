#include "hisi_fb.h"
#include "lcdkit_panel.h"
#include "lcdkit_dbg.h"
#include "lcdkit_disp.h"
#include "lcdkit_parse.h"

/*
*name:lcdkit_info_init
*function:lcd_panel_info init
*@pinfo:lcd panel info
*/

//lint -save -e144 -e578 -e647
void lcdkit_info_init(void* pdata)
{
    struct hisi_panel_info* pinfo;

    pinfo = (struct hisi_panel_info*) pdata;
    pinfo->xres = lcdkit_info.panel_infos.xres;
    pinfo->yres = lcdkit_info.panel_infos.yres;
    pinfo->width = lcdkit_info.panel_infos.width;
    pinfo->height = lcdkit_info.panel_infos.height;
    pinfo->esd_enable = lcdkit_info.panel_infos.esd_support;
    pinfo->bl_min = lcdkit_info.panel_infos.bl_level_min;
    pinfo->bl_max = lcdkit_info.panel_infos.bl_level_max;

    pinfo->pxl_clk_rate *= 1000000UL;
    pinfo->mipi.max_tx_esc_clk *= 1000000;

    /*for fps*/
    if (lcdkit_info.panel_infos.fps_func_switch){
        pinfo->fps = 60;
        pinfo->fps_updt = 60;
    }

    if (pinfo->bl_set_type == BL_SET_BY_BLPWM)
    {
        pinfo->blpwm_input_ena = 1;
    }

    if (pinfo->ifbc_type == IFBC_TYPE_ORISE3X)
    {
        pinfo->ifbc_cmp_dat_rev0 = 0;
        pinfo->ifbc_cmp_dat_rev1 = 0;
        pinfo->ifbc_auto_sel = 1;
        pinfo->ifbc_orise_ctr = 1;

        //FIXME:
        pinfo->pxl_clk_rate_div = 3;
        pinfo->ifbc_orise_ctl = IFBC_ORISE_CTL_FRAME;
    }

    if (pinfo->ifbc_type == IFBC_TYPE_VESA3X_SINGLE) {
        pinfo->pxl_clk_rate_div = 3;

        /* dsc parameter info */
        pinfo->vesa_dsc.bits_per_component = 8;
        pinfo->vesa_dsc.bits_per_pixel = 8;
        pinfo->vesa_dsc.slice_width = 719;
        pinfo->vesa_dsc.slice_height = 31;

        pinfo->vesa_dsc.initial_xmit_delay = 512;
        pinfo->vesa_dsc.first_line_bpg_offset = 12;
        pinfo->vesa_dsc.mux_word_size = 48;

        /*  DSC_CTRL */
        pinfo->vesa_dsc.block_pred_enable = 1;
        pinfo->vesa_dsc.linebuf_depth = 9;

        /* RC_PARAM3 */
        pinfo->vesa_dsc.initial_offset = 6144;

        /* FLATNESS_QP_TH */
        pinfo->vesa_dsc.flatness_min_qp = 3;
        pinfo->vesa_dsc.flatness_max_qp = 12;

        /* DSC_PARAM4 */
        pinfo->vesa_dsc.rc_edge_factor = 0x6;
        pinfo->vesa_dsc.rc_model_size = 8192;

        /* DSC_RC_PARAM5: 0x330b0b */
        pinfo->vesa_dsc.rc_tgt_offset_lo = (0x330b0b >> 20) & 0xF;
        pinfo->vesa_dsc.rc_tgt_offset_hi = (0x330b0b >> 16) & 0xF;
        pinfo->vesa_dsc.rc_quant_incr_limit1 = (0x330b0b >> 8) & 0x1F;
        pinfo->vesa_dsc.rc_quant_incr_limit0 = (0x330b0b >> 0) & 0x1F;

        /* DSC_RC_BUF_THRESH0: 0xe1c2a38 */
        pinfo->vesa_dsc.rc_buf_thresh0 = (0xe1c2a38 >> 24) & 0xFF;
        pinfo->vesa_dsc.rc_buf_thresh1 = (0xe1c2a38 >> 16) & 0xFF;
        pinfo->vesa_dsc.rc_buf_thresh2 = (0xe1c2a38 >> 8) & 0xFF;
        pinfo->vesa_dsc.rc_buf_thresh3 = (0xe1c2a38 >> 0) & 0xFF;

        /* DSC_RC_BUF_THRESH1: 0x46546269 */
        pinfo->vesa_dsc.rc_buf_thresh4 = (0x46546269 >> 24) & 0xFF;
        pinfo->vesa_dsc.rc_buf_thresh5 = (0x46546269 >> 16) & 0xFF;
        pinfo->vesa_dsc.rc_buf_thresh6 = (0x46546269 >> 8) & 0xFF;
        pinfo->vesa_dsc.rc_buf_thresh7 = (0x46546269 >> 0) & 0xFF;

        /* DSC_RC_BUF_THRESH2: 0x7077797b */
        pinfo->vesa_dsc.rc_buf_thresh8 = (0x7077797b >> 24) & 0xFF;
        pinfo->vesa_dsc.rc_buf_thresh9 = (0x7077797b >> 16) & 0xFF;
        pinfo->vesa_dsc.rc_buf_thresh10 = (0x7077797b >> 8) & 0xFF;
        pinfo->vesa_dsc.rc_buf_thresh11 = (0x7077797b >> 0) & 0xFF;

        /* DSC_RC_BUF_THRESH3: 0x7d7e0000 */
        pinfo->vesa_dsc.rc_buf_thresh12 = (0x7d7e0000 >> 24) & 0xFF;
        pinfo->vesa_dsc.rc_buf_thresh13 = (0x7d7e0000 >> 16) & 0xFF;

        /* DSC_RC_RANGE_PARAM0: 0x1020100 */
        pinfo->vesa_dsc.range_min_qp0 = (0x1020100 >> 27) & 0x1F;
        pinfo->vesa_dsc.range_max_qp0 = (0x1020100 >> 22) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset0 = (0x1020100 >> 16) & 0x3F;
        pinfo->vesa_dsc.range_min_qp1 = (0x1020100 >> 11) & 0x1F;
        pinfo->vesa_dsc.range_max_qp1 = (0x1020100 >> 6) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset1 = (0x1020100 >> 0) & 0x3F;

        /* DSC_RC_RANGE_PARAM1: 0x94009be */
        pinfo->vesa_dsc.range_min_qp2 = (0x94009be >> 27) & 0x1F;
        pinfo->vesa_dsc.range_max_qp2 = (0x94009be >> 22) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset2 = (0x94009be >> 16) & 0x3F;
        pinfo->vesa_dsc.range_min_qp3 = (0x94009be >> 11) & 0x1F;
        pinfo->vesa_dsc.range_max_qp3 = (0x94009be >> 6) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset3 = (0x94009be >> 0) & 0x3F;

        /* DSC_RC_RANGE_PARAM2, 0x19fc19fa */
        pinfo->vesa_dsc.range_min_qp4 = (0x19fc19fa >> 27) & 0x1F;
        pinfo->vesa_dsc.range_max_qp4 = (0x19fc19fa >> 22) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset4 = (0x19fc19fa >> 16) & 0x3F;
        pinfo->vesa_dsc.range_min_qp5 = (0x19fc19fa >> 11) & 0x1F;
        pinfo->vesa_dsc.range_max_qp5 = (0x19fc19fa >> 6) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset5 = (0x19fc19fa >> 0) & 0x3F;

        /* DSC_RC_RANGE_PARAM3, 0x19f81a38 */
        pinfo->vesa_dsc.range_min_qp6 = (0x19f81a38 >> 27) & 0x1F;
        pinfo->vesa_dsc.range_max_qp6 = (0x19f81a38 >> 22) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset6 = (0x19f81a38 >> 16) & 0x3F;
        pinfo->vesa_dsc.range_min_qp7 = (0x19f81a38 >> 11) & 0x1F;
        pinfo->vesa_dsc.range_max_qp7 = (0x19f81a38 >> 6) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset7 = (0x19f81a38 >> 0) & 0x3F;

        /* DSC_RC_RANGE_PARAM4, 0x1a781ab6 */
        pinfo->vesa_dsc.range_min_qp8 = (0x1a781ab6 >> 27) & 0x1F;
        pinfo->vesa_dsc.range_max_qp8 = (0x1a781ab6 >> 22) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset8 = (0x1a781ab6 >> 16) & 0x3F;
        pinfo->vesa_dsc.range_min_qp9 = (0x1a781ab6 >> 11) & 0x1F;
        pinfo->vesa_dsc.range_max_qp9 = (0x1a781ab6 >> 6) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset9 = (0x1a781ab6 >> 0) & 0x3F;

        /* DSC_RC_RANGE_PARAM5, 0x2af62b34 */
        pinfo->vesa_dsc.range_min_qp10 = (0x2af62b34 >> 27) & 0x1F;
        pinfo->vesa_dsc.range_max_qp10 = (0x2af62b34 >> 22) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset10 = (0x2af62b34 >> 16) & 0x3F;
        pinfo->vesa_dsc.range_min_qp11 = (0x2af62b34 >> 11) & 0x1F;
        pinfo->vesa_dsc.range_max_qp11 = (0x2af62b34 >> 6) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset11 = (0x2af62b34 >> 0) & 0x3F;

        /* DSC_RC_RANGE_PARAM6, 0x2b743b74 */
        pinfo->vesa_dsc.range_min_qp12 = (0x2b743b74 >> 27) & 0x1F;
        pinfo->vesa_dsc.range_max_qp12 = (0x2b743b74 >> 22) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset12 = (0x2b743b74 >> 16) & 0x3F;
        pinfo->vesa_dsc.range_min_qp13 = (0x2b743b74 >> 11) & 0x1F;
        pinfo->vesa_dsc.range_max_qp13 = (0x2b743b74 >> 6) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset13 = (0x2b743b74 >> 0) & 0x3F;

        /* DSC_RC_RANGE_PARAM7, 0x6bf40000 */
        pinfo->vesa_dsc.range_min_qp14 = (0x6bf40000 >> 27) & 0x1F;
        pinfo->vesa_dsc.range_max_qp14 = (0x6bf40000 >> 22) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset14 = (0x6bf40000 >> 16) & 0x3F;

        if (pinfo->pxl_clk_rate_div > 1) {
            pinfo->ldi.h_back_porch /= pinfo->pxl_clk_rate_div;
            pinfo->ldi.h_front_porch /= pinfo->pxl_clk_rate_div;
            pinfo->ldi.h_pulse_width /= pinfo->pxl_clk_rate_div;
        }
        /* IFBC Setting end */
    }
    if (pinfo->ifbc_type == IFBC_TYPE_VESA3_75X_DUAL) {
        //pinfo->bpp = LCD_RGB101010;
        //pinfo->mipi.color_mode = DSI_30BITS_1;
        pinfo->vesa_dsc.bits_per_component = 10;
        pinfo->vesa_dsc.linebuf_depth = 11;
        pinfo->vesa_dsc.bits_per_pixel = 8;
        pinfo->vesa_dsc.initial_xmit_delay = 512;

        pinfo->vesa_dsc.slice_width = 719;//1439
        pinfo->vesa_dsc.slice_height = 7;//31;

        pinfo->vesa_dsc.first_line_bpg_offset = 12;
        pinfo->vesa_dsc.mux_word_size = 48;

        /* DSC_CTRL */
        pinfo->vesa_dsc.block_pred_enable = 1;//0;

        /* RC_PARAM3 */
        pinfo->vesa_dsc.initial_offset = 6144;

        /* FLATNESS_QP_TH */
        pinfo->vesa_dsc.flatness_min_qp = 7;
        pinfo->vesa_dsc.flatness_max_qp = 16;

        /* DSC_PARAM4 */
        pinfo->vesa_dsc.rc_edge_factor= 0x6;
        pinfo->vesa_dsc.rc_model_size = 8192;

        /* DSC_RC_PARAM5: 0x330f0f */
        pinfo->vesa_dsc.rc_tgt_offset_lo = (0x330f0f >> 20) & 0xF;
        pinfo->vesa_dsc.rc_tgt_offset_hi = (0x330f0f >> 16) & 0xF;
        pinfo->vesa_dsc.rc_quant_incr_limit1 = (0x330f0f >> 8) & 0x1F;
        pinfo->vesa_dsc.rc_quant_incr_limit0 = (0x330f0f >> 0) & 0x1F;

        /* DSC_RC_BUF_THRESH0: 0xe1c2a38 */
        pinfo->vesa_dsc.rc_buf_thresh0 = (0xe1c2a38 >> 24) & 0xFF;
        pinfo->vesa_dsc.rc_buf_thresh1 = (0xe1c2a38 >> 16) & 0xFF;
        pinfo->vesa_dsc.rc_buf_thresh2 = (0xe1c2a38 >> 8) & 0xFF;
        pinfo->vesa_dsc.rc_buf_thresh3 = (0xe1c2a38 >> 0) & 0xFF;

        /* DSC_RC_BUF_THRESH1: 0x46546269 */
        pinfo->vesa_dsc.rc_buf_thresh4 = (0x46546269 >> 24) & 0xFF;
        pinfo->vesa_dsc.rc_buf_thresh5 = (0x46546269 >> 16) & 0xFF;
        pinfo->vesa_dsc.rc_buf_thresh6 = (0x46546269 >> 8) & 0xFF;
        pinfo->vesa_dsc.rc_buf_thresh7 = (0x46546269 >> 0) & 0xFF;

        /* DSC_RC_BUF_THRESH2: 0x7077797b */
        pinfo->vesa_dsc.rc_buf_thresh8 = (0x7077797b >> 24) & 0xFF;
        pinfo->vesa_dsc.rc_buf_thresh9 = (0x7077797b >> 16) & 0xFF;
        pinfo->vesa_dsc.rc_buf_thresh10 = (0x7077797b >> 8) & 0xFF;
        pinfo->vesa_dsc.rc_buf_thresh11 = (0x7077797b >> 0) & 0xFF;

        /* DSC_RC_BUF_THRESH3: 0x7d7e0000 */
        pinfo->vesa_dsc.rc_buf_thresh12 = (0x7d7e0000 >> 24) & 0xFF;
        pinfo->vesa_dsc.rc_buf_thresh13 = (0x7d7e0000 >> 16) & 0xFF;

        /* DSC_RC_RANGE_PARAM0: 0x2022200 */
        pinfo->vesa_dsc.range_min_qp0 = (0x2022200 >> 27) & 0x1F;
        pinfo->vesa_dsc.range_max_qp0 = (0x2022200 >> 22) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset0 = (0x2022200 >> 16) & 0x3F;
        pinfo->vesa_dsc.range_min_qp1 = (0x2022200 >> 11) & 0x1F;
        pinfo->vesa_dsc.range_max_qp1 = (0x2022200 >> 6) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset1 = (0x2022200 >> 0) & 0x3F;

        /* DSC_RC_RANGE_PARAM1: 0x94009be */
        pinfo->vesa_dsc.range_min_qp2 = 5;//(0x94009be >> 27) & 0x1F;
        pinfo->vesa_dsc.range_max_qp2 = 9;//(0x94009be >> 22) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset2 = (0x94009be >> 16) & 0x3F;
        pinfo->vesa_dsc.range_min_qp3 = 5;//(0x94009be >> 11) & 0x1F;
        pinfo->vesa_dsc.range_max_qp3 = 10;//(0x94009be >> 6) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset3 = (0x94009be >> 0) & 0x3F;

        /* DSC_RC_RANGE_PARAM2, 0x19fc19fa */
        pinfo->vesa_dsc.range_min_qp4 = 7;//(0x19fc19fa >> 27) & 0x1F;
        pinfo->vesa_dsc.range_max_qp4 = 11;//(0x19fc19fa >> 22) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset4 = (0x19fc19fa >> 16) & 0x3F;
        pinfo->vesa_dsc.range_min_qp5 = 7;//(0x19fc19fa >> 11) & 0x1F;
        pinfo->vesa_dsc.range_max_qp5 = 11;//(0x19fc19fa >> 6) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset5 = (0x19fc19fa >> 0) & 0x3F;

        /* DSC_RC_RANGE_PARAM3, 0x19f81a38 */
        pinfo->vesa_dsc.range_min_qp6 = 7;//(0x19f81a38 >> 27) & 0x1F;
        pinfo->vesa_dsc.range_max_qp6 = 11;//(0x19f81a38 >> 22) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset6 = (0x19f81a38 >> 16) & 0x3F;
        pinfo->vesa_dsc.range_min_qp7 = 7;//(0x19f81a38 >> 11) & 0x1F;
        pinfo->vesa_dsc.range_max_qp7 = 12;//(0x19f81a38 >> 6) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset7 = (0x19f81a38 >> 0) & 0x3F;

        /* DSC_RC_RANGE_PARAM4, 0x1a781ab6 */
        pinfo->vesa_dsc.range_min_qp8 = 7;//(0x1a781ab6 >> 27) & 0x1F;
        pinfo->vesa_dsc.range_max_qp8 = 13;//(0x1a781ab6 >> 22) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset8 = (0x1a781ab6 >> 16) & 0x3F;
        pinfo->vesa_dsc.range_min_qp9 = 7;//(0x1a781ab6 >> 11) & 0x1F;
        pinfo->vesa_dsc.range_max_qp9 = 14;//(0x1a781ab6 >> 6) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset9 = (0x1a781ab6 >> 0) & 0x3F;

        /* DSC_RC_RANGE_PARAM5, 0x2af62b34 */
        pinfo->vesa_dsc.range_min_qp10 = 9;//(0x2af62b34 >> 27) & 0x1F;
        pinfo->vesa_dsc.range_max_qp10 = 15;//(0x2af62b34 >> 22) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset10 = (0x2af62b34 >> 16) & 0x3F;
        pinfo->vesa_dsc.range_min_qp11 = 9;//(0x2af62b34 >> 11) & 0x1F;
        pinfo->vesa_dsc.range_max_qp11 = 16;//(0x2af62b34 >> 6) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset11 = (0x2af62b34 >> 0) & 0x3F;

        /* DSC_RC_RANGE_PARAM6, 0x2b743b74 */
        pinfo->vesa_dsc.range_min_qp12 = 9;//(0x2b743b74 >> 27) & 0x1F;
        pinfo->vesa_dsc.range_max_qp12 = 17;//(0x2b743b74 >> 22) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset12 = (0x2b743b74 >> 16) & 0x3F;
        pinfo->vesa_dsc.range_min_qp13 = 11;//(0x2b743b74 >> 11) & 0x1F;
        pinfo->vesa_dsc.range_max_qp13 = 17;//(0x2b743b74 >> 6) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset13 = (0x2b743b74 >> 0) & 0x3F;

        /* DSC_RC_RANGE_PARAM7, 0x6bf40000 */
        pinfo->vesa_dsc.range_min_qp14 = 17;//(0x6bf40000 >> 27) & 0x1F;
        pinfo->vesa_dsc.range_max_qp14 = 19;//(0x6bf40000 >> 22) & 0x1F;
        pinfo->vesa_dsc.range_bpg_offset14 = (0x6bf40000 >> 16) & 0x3F;
    }

	if (pinfo->ifbc_type == IFBC_TYPE_VESA3X_DUAL) {
		pinfo->vesa_dsc.bits_per_component = 8;
		pinfo->vesa_dsc.linebuf_depth = 9;
		pinfo->vesa_dsc.bits_per_pixel = 8;
		pinfo->vesa_dsc.initial_xmit_delay = 512;

		pinfo->vesa_dsc.slice_width = 719;//1439
		pinfo->vesa_dsc.slice_height = 7;//31;

		pinfo->vesa_dsc.first_line_bpg_offset = 12;
		pinfo->vesa_dsc.mux_word_size = 48;

		/* DSC_CTRL */
		pinfo->vesa_dsc.block_pred_enable = 1;//0;

		/* RC_PARAM3 */
		pinfo->vesa_dsc.initial_offset = 6144;

		/* FLATNESS_QP_TH */
		pinfo->vesa_dsc.flatness_min_qp = 3;
		pinfo->vesa_dsc.flatness_max_qp = 12;

		/* DSC_PARAM4 */
		pinfo->vesa_dsc.rc_edge_factor= 0x6;
		pinfo->vesa_dsc.rc_model_size = 8192;

		/* DSC_RC_PARAM5: 0x330b0b */
		pinfo->vesa_dsc.rc_tgt_offset_lo = (0x330b0b >> 20) & 0xF;
		pinfo->vesa_dsc.rc_tgt_offset_hi = (0x330b0b >> 16) & 0xF;
		pinfo->vesa_dsc.rc_quant_incr_limit1 = (0x330b0b >> 8) & 0x1F;
		pinfo->vesa_dsc.rc_quant_incr_limit0 = (0x330b0b >> 0) & 0x1F;

		/* DSC_RC_BUF_THRESH0: 0xe1c2a38 */
		pinfo->vesa_dsc.rc_buf_thresh0 = (0xe1c2a38 >> 24) & 0xFF;
		pinfo->vesa_dsc.rc_buf_thresh1 = (0xe1c2a38 >> 16) & 0xFF;
		pinfo->vesa_dsc.rc_buf_thresh2 = (0xe1c2a38 >> 8) & 0xFF;
		pinfo->vesa_dsc.rc_buf_thresh3 = (0xe1c2a38 >> 0) & 0xFF;

		/* DSC_RC_BUF_THRESH1: 0x46546269 */
		pinfo->vesa_dsc.rc_buf_thresh4 = (0x46546269 >> 24) & 0xFF;
		pinfo->vesa_dsc.rc_buf_thresh5 = (0x46546269 >> 16) & 0xFF;
		pinfo->vesa_dsc.rc_buf_thresh6 = (0x46546269 >> 8) & 0xFF;
		pinfo->vesa_dsc.rc_buf_thresh7 = (0x46546269 >> 0) & 0xFF;

		/* DSC_RC_BUF_THRESH2: 0x7077797b */
		pinfo->vesa_dsc.rc_buf_thresh8 = (0x7077797b >> 24) & 0xFF;
		pinfo->vesa_dsc.rc_buf_thresh9 = (0x7077797b >> 16) & 0xFF;
		pinfo->vesa_dsc.rc_buf_thresh10 = (0x7077797b >> 8) & 0xFF;
		pinfo->vesa_dsc.rc_buf_thresh11 = (0x7077797b >> 0) & 0xFF;

		/* DSC_RC_BUF_THRESH3: 0x7d7e0000 */
		pinfo->vesa_dsc.rc_buf_thresh12 = (0x7d7e0000 >> 24) & 0xFF;
		pinfo->vesa_dsc.rc_buf_thresh13 = (0x7d7e0000 >> 16) & 0xFF;

		/* DSC_RC_RANGE_PARAM0: 0x1020100 */
		pinfo->vesa_dsc.range_min_qp0 = (0x1020100 >> 27) & 0x1F; //lint !e572
		pinfo->vesa_dsc.range_max_qp0 = (0x1020100 >> 22) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset0 = (0x1020100 >> 16) & 0x3F;
		pinfo->vesa_dsc.range_min_qp1 = (0x1020100 >> 11) & 0x1F;
		pinfo->vesa_dsc.range_max_qp1 = (0x1020100 >> 6) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset1 = (0x1020100 >> 0) & 0x3F;

		/* DSC_RC_RANGE_PARAM1: 0x94009be */
		pinfo->vesa_dsc.range_min_qp2 = (0x94009be >> 27) & 0x1F;
		pinfo->vesa_dsc.range_max_qp2 = (0x94009be >> 22) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset2 = (0x94009be >> 16) & 0x3F;
		pinfo->vesa_dsc.range_min_qp3 = (0x94009be >> 11) & 0x1F;
		pinfo->vesa_dsc.range_max_qp3 = (0x94009be >> 6) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset3 = (0x94009be >> 0) & 0x3F;

		/* DSC_RC_RANGE_PARAM2, 0x19fc19fa */
		pinfo->vesa_dsc.range_min_qp4 = (0x19fc19fa >> 27) & 0x1F;
		pinfo->vesa_dsc.range_max_qp4 = (0x19fc19fa >> 22) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset4 = (0x19fc19fa >> 16) & 0x3F;
		pinfo->vesa_dsc.range_min_qp5 = (0x19fc19fa >> 11) & 0x1F;
		pinfo->vesa_dsc.range_max_qp5 = (0x19fc19fa >> 6) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset5 = (0x19fc19fa >> 0) & 0x3F;

		/* DSC_RC_RANGE_PARAM3, 0x19f81a38 */
		pinfo->vesa_dsc.range_min_qp6 = (0x19f81a38 >> 27) & 0x1F;
		pinfo->vesa_dsc.range_max_qp6 = (0x19f81a38 >> 22) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset6 = (0x19f81a38 >> 16) & 0x3F;
		pinfo->vesa_dsc.range_min_qp7 = (0x19f81a38 >> 11) & 0x1F;
		pinfo->vesa_dsc.range_max_qp7 = (0x19f81a38 >> 6) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset7 = (0x19f81a38 >> 0) & 0x3F;

		/* DSC_RC_RANGE_PARAM4, 0x1a781ab6 */
		pinfo->vesa_dsc.range_min_qp8 = (0x1a781ab6 >> 27) & 0x1F;
		pinfo->vesa_dsc.range_max_qp8 = (0x1a781ab6 >> 22) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset8 = (0x1a781ab6 >> 16) & 0x3F;
		pinfo->vesa_dsc.range_min_qp9 = (0x1a781ab6 >> 11) & 0x1F;
		pinfo->vesa_dsc.range_max_qp9 = (0x1a781ab6 >> 6) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset9 = (0x1a781ab6 >> 0) & 0x3F;

		/* DSC_RC_RANGE_PARAM5, 0x2af62b34 */
		pinfo->vesa_dsc.range_min_qp10 = (0x2af62b34 >> 27) & 0x1F;
		pinfo->vesa_dsc.range_max_qp10 = (0x2af62b34 >> 22) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset10 = (0x2af62b34 >> 16) & 0x3F;
		pinfo->vesa_dsc.range_min_qp11 = (0x2af62b34 >> 11) & 0x1F;
		pinfo->vesa_dsc.range_max_qp11 = (0x2af62b34 >> 6) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset11 = (0x2af62b34 >> 0) & 0x3F;

		/* DSC_RC_RANGE_PARAM6, 0x2b743b74 */
		pinfo->vesa_dsc.range_min_qp12 = (0x2b743b74 >> 27) & 0x1F;
		pinfo->vesa_dsc.range_max_qp12 = (0x2b743b74 >> 22) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset12 = (0x2b743b74 >> 16) & 0x3F;
		pinfo->vesa_dsc.range_min_qp13 = (0x2b743b74 >> 11) & 0x1F;
		pinfo->vesa_dsc.range_max_qp13 = (0x2b743b74 >> 6) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset13 = (0x2b743b74 >> 0) & 0x3F;

		/* DSC_RC_RANGE_PARAM7, 0x6bf40000 */
		pinfo->vesa_dsc.range_min_qp14 = (0x6bf40000 >> 27) & 0x1F;
		pinfo->vesa_dsc.range_max_qp14 = (0x6bf40000 >> 22) & 0x1F;
		pinfo->vesa_dsc.range_bpg_offset14 = (0x6bf40000 >> 16) & 0x3F;
	}
    /*ce rely on acm*/
    if (pinfo->acm_support == 0)
    {
        pinfo->acm_ce_support = 0;
    }

}

int lcdkit_cmds_to_dsi_cmds(struct lcdkit_dsi_panel_cmds* lcdkit_cmds, struct dsi_cmd_desc* cmd)
{
    struct dsi_cmd_desc* dsi_cmd;
    int i = 0;

    dsi_cmd = cmd;

    if (lcdkit_cmds == NULL)
    {
        LCDKIT_ERR("lcdkit_cmds is null point!\n");
        return -EINVAL;
    }

    lcdkit_dump_cmds(lcdkit_cmds);

    for (i = 0; i < lcdkit_cmds->cmd_cnt; i++)
    {
        dsi_cmd[i].dtype = lcdkit_cmds->cmds[i].dtype;
        dsi_cmd[i].vc =  lcdkit_cmds->cmds[i].vc;
        dsi_cmd[i].wait =  lcdkit_cmds->cmds[i].wait;
        dsi_cmd[i].waittype =  lcdkit_cmds->cmds[i].waittype;
        dsi_cmd[i].dlen =  lcdkit_cmds->cmds[i].dlen;
        dsi_cmd[i].payload = lcdkit_cmds->cmds[i].payload;
    }

    return 0;

}

/*
 *  dsi send cmds
*/
void lcdkit_dsi_tx(void* pdata, struct lcdkit_dsi_panel_cmds* cmds)
{
    struct hisi_fb_data_type* hisifd = NULL;
    char __iomem* mipi_dsi0_base = NULL;
    int ret = 0;
    struct dsi_cmd_desc* cmd;

    if (!cmds || cmds->cmd_cnt <= 0){
        LCDKIT_DEBUG("cmd cnt is 0!\n");
        return ;
    }

    cmd = (struct dsi_cmd_desc*)kzalloc(sizeof(struct dsi_cmd_desc) * cmds->cmd_cnt, GFP_KERNEL);
    if (!cmd)
    {
        LCDKIT_ERR("cmd kzalloc fail!\n");
        return ;
    }
    ret = lcdkit_cmds_to_dsi_cmds(cmds, cmd);

    if (ret)
    {
        LCDKIT_ERR("lcdkit_cmds convert fail!\n");
        kfree(cmd);
        return ;
    }

    hisifd = (struct hisi_fb_data_type*) pdata;
    mipi_dsi0_base = hisifd->mipi_dsi0_base;

    (void)mipi_dsi_cmds_tx(cmd, cmds->cmd_cnt, mipi_dsi0_base);

    kfree(cmd);

    return;

}

int lcdkit_dsi_rx(void* pdata, uint32_t* out, int len, struct lcdkit_dsi_panel_cmds* cmds)
{
    struct hisi_fb_data_type* hisifd = NULL;
    char __iomem* mipi_dsi0_base = NULL;
    int ret = 0;
    struct dsi_cmd_desc* cmd;
    cmd = kzalloc(sizeof(struct dsi_cmd_desc) * cmds->cmd_cnt, GFP_KERNEL);

    ret = lcdkit_cmds_to_dsi_cmds(cmds, cmd);

    if (ret)
    {
       LCDKIT_ERR("lcdkit_cmds convert fail!\n");
	kfree(cmd);
       return ret;
    }

    hisifd = (struct hisi_fb_data_type*) pdata;
    mipi_dsi0_base = hisifd->mipi_dsi0_base;

    ret = mipi_dsi_cmds_rx(out, cmd, cmds->cmd_cnt, mipi_dsi0_base);
    if(ret)
    {
        LCDKIT_INFO("lcdkit_dsi_rx failed!\n");
    }
    kfree(cmd);

    return ret;

}

/*switch lp to hs or hs to lp*/
void lcdkit_switch_hs_lp(void* pdata, bool enable)
{
    struct hisi_fb_data_type* hisifd = NULL;
    char __iomem* mipi_dsi0_base = NULL;

    hisifd = (struct hisi_fb_data_type*) pdata;
    mipi_dsi0_base = hisifd->mipi_dsi0_base;

    if (is_mipi_cmd_panel(hisifd))
    {
        set_reg(mipi_dsi0_base + MIPIDSI_CMD_MODE_CFG_OFFSET, enable, 1, 14);
        set_reg(mipi_dsi0_base + MIPIDSI_CMD_MODE_CFG_OFFSET, enable, 1, 9);
    }
    else
    {
        set_reg(mipi_dsi0_base + MIPIDSI_VID_MODE_CFG_OFFSET, 0x1, 1, 15);
    }

}

void lcdkit_hs_lp_switch(void* pdata, int mode)
{
    struct hisi_fb_data_type* hisifd = NULL;
    char __iomem* mipi_dsi0_base = NULL;

    hisifd = (struct hisi_fb_data_type*) pdata;
    mipi_dsi0_base = hisifd->mipi_dsi0_base;

    switch(mode)
    {
        case LCDKIT_DSI_LP_MODE:
            LCDKIT_DEBUG("lcdkit switch to lp mode\n");
            /* set mipi in lp mode */
            set_reg(mipi_dsi0_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0x7f, 7, 8);
            set_reg(mipi_dsi0_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0xf, 4, 16);
            set_reg(mipi_dsi0_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0x1, 1, 24);
            break;
        case LCDKIT_DSI_HS_MODE:
            LCDKIT_DEBUG("lcdkit switch to hs mode\n");
            /* set mipi in hs mode */
            set_reg(mipi_dsi0_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0x0, 7, 8);
            set_reg(mipi_dsi0_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0x0, 4, 16);
            set_reg(mipi_dsi0_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0x0, 1, 24);
            break;
        default:
            LCDKIT_ERR("lcdkit set unknown mipi mode:%d\n", mode);
            break;
    }
}

void lcdkit_mipi_dsi_max_return_packet_size(void* pdata, struct lcdkit_dsi_cmd_desc* cm)
{
    uint32_t hdr = 0;
    struct hisi_fb_data_type* hisifd = NULL;
    char __iomem* mipi_dsi0_base = NULL;

    hisifd = (struct hisi_fb_data_type*) pdata;
    mipi_dsi0_base = hisifd->mipi_dsi0_base;

    /* fill up header */
    hdr |= DSI_HDR_DTYPE(cm->dtype);
    hdr |= DSI_HDR_VC(cm->vc);
    hdr |= DSI_HDR_WC(cm->dlen);
    set_reg(mipi_dsi0_base + MIPIDSI_GEN_HDR_OFFSET, hdr, 24, 0);
}

int lcdkit_mipi_dsi_read_compare(struct mipi_dsi_read_compare_data* data,
                                 void* pdata)
{
    uint32_t* read_value = NULL;
    uint32_t* expected_value = NULL;
    uint32_t* read_mask = NULL;
    char** reg_name = NULL;
    int log_on = 0;
    struct lcdkit_dsi_cmd_desc* cmds = NULL;
    int cnt = 0;
    int cnt_not_match = 0;
    int ret = 0;
    int i;

    BUG_ON(data == NULL);

    read_value = data->read_value;
    expected_value = data->expected_value;
    read_mask = data->read_mask;
    reg_name = data->reg_name;
    log_on = data->log_on;

    cmds = data->cmds;
    cnt = data->cnt;

    lcdkit_dsi_rx(pdata, read_value, 1, cmds);

    for (i = 0; i < cnt; i++)
    {
        if (log_on)
        {
            LCDKIT_INFO("Read reg %s: 0x%x, value = 0x%x\n",
                        reg_name[i], cmds[i].payload[0], read_value[i]);
        }

        if (expected_value[i] != (read_value[i] & read_mask[i]))
        {
            cnt_not_match++;
        }
    }

    return cnt_not_match;
}

bool lcdkit_is_cmd_panel(void)
{
    if ( lcdkit_info.panel_infos.lcd_disp_type & (PANEL_MIPI_CMD | PANEL_DUAL_MIPI_CMD) )
    { 
        return true; 
    }

    return false;
}

void lcdkit_updt_porch(struct platform_device* pdev, int scence)
{
    struct hisi_fb_data_type* hisifd = NULL;
    struct hisi_panel_info* pinfo = NULL;

    BUG_ON(pdev == NULL);
    hisifd = platform_get_drvdata(pdev);
    BUG_ON(hisifd == NULL);
    pinfo = &(hisifd->panel_info);

    switch (scence)
    {
        case LCDKIT_FPS_SCENCE_IDLE:
            pinfo->ldi_updt.h_back_porch = lcdkit_info.panel_infos.fps_30_porch_param.buf[0];
            pinfo->ldi_updt.h_front_porch = lcdkit_info.panel_infos.fps_30_porch_param.buf[1];
            pinfo->ldi_updt.h_pulse_width = lcdkit_info.panel_infos.fps_30_porch_param.buf[2];
            pinfo->ldi_updt.v_back_porch = lcdkit_info.panel_infos.fps_30_porch_param.buf[3];
            pinfo->ldi_updt.v_front_porch = lcdkit_info.panel_infos.fps_30_porch_param.buf[4];
            pinfo->ldi_updt.v_pulse_width = lcdkit_info.panel_infos.fps_30_porch_param.buf[5];
            LCDKIT_INFO("scence is LCDKIT_FPS_SCENCE_IDLE, framerate is 30fps\n");
            break;

        case LCDKIT_FPS_SCENCE_EBOOK:
            pinfo->ldi_updt.h_back_porch = lcdkit_info.panel_infos.fps_55_porch_param.buf[0];
            pinfo->ldi_updt.h_front_porch = lcdkit_info.panel_infos.fps_55_porch_param.buf[1];
            pinfo->ldi_updt.h_pulse_width = lcdkit_info.panel_infos.fps_55_porch_param.buf[2];
            pinfo->ldi_updt.v_back_porch = lcdkit_info.panel_infos.fps_55_porch_param.buf[3];
            pinfo->ldi_updt.v_front_porch = lcdkit_info.panel_infos.fps_55_porch_param.buf[4];
            pinfo->ldi_updt.v_pulse_width = lcdkit_info.panel_infos.fps_55_porch_param.buf[5];
            LCDKIT_INFO("scence is LCD_FPS_SCENCE_EBOOK, framerate is 55fps!\n");
            break;

        default:
            pinfo->ldi_updt.h_back_porch = lcdkit_info.panel_infos.fps_60_porch_param.buf[0];
            pinfo->ldi_updt.h_front_porch = lcdkit_info.panel_infos.fps_60_porch_param.buf[1];
            pinfo->ldi_updt.h_pulse_width = lcdkit_info.panel_infos.fps_60_porch_param.buf[2];
            pinfo->ldi_updt.v_back_porch = lcdkit_info.panel_infos.fps_60_porch_param.buf[3];
            pinfo->ldi_updt.v_front_porch = lcdkit_info.panel_infos.fps_60_porch_param.buf[4];
            pinfo->ldi_updt.v_pulse_width = lcdkit_info.panel_infos.fps_60_porch_param.buf[5];
            LCDKIT_INFO("scence is default, framerate is 60fps!\n");
            break;
    }
}

void lcdkit_lp2hs_mipi_test(void* pdata)
{
    u32 lp2hs_mipi_check_read_value[1] = {0};

    struct lcdkit_dsi_read_compare_data g_lp2hs_mipi_check_data =
    {
        .read_value = lp2hs_mipi_check_read_value,
        .expected_value = lcdkit_info.panel_infos.lp2hs_mipi_check_expected_value,
        .read_mask = lcdkit_info.panel_infos.lp2hs_mipi_check_read_mask,
        .reg_name = "power mode",
        .log_on = 1,
        .cmds = &lcdkit_info.panel_infos.lp2hs_mipi_check_read_cmds,
        .cnt = lcdkit_info.panel_infos.lp2hs_mipi_check_read_cmds.cmd_cnt,
    };

    if (lcdkit_info.panel_infos.lp2hs_mipi_check_support)
    {
        lcdkit_dsi_tx(pdata, &lcdkit_info.panel_infos.lp2hs_mipi_check_write_cmds);

        if (!lcdkit_mipi_dsi_read_compare(&g_lp2hs_mipi_check_data, pdata))
        {
            LCDKIT_INFO("lp2hs test OK\n");
            lcdkit_info.panel_infos.g_lp2hs_mipi_check_result = true;
        }
        else
        {
            LCDKIT_INFO("lp2hs test fail\n");
            lcdkit_info.panel_infos.g_lp2hs_mipi_check_result = false;
        }
    }
}
#if defined (CONFIG_HISI_FB_970)
void lcdkit_effect_switch_ctrl(void* pdata, bool ctrl)
{
    struct hisi_fb_data_type* hisifd = NULL;
    struct hisi_panel_info* pinfo = NULL;
    char __iomem* mipi_dsi0_base = NULL;
    char __iomem* dpp_base = NULL;
    char __iomem* lcp_base = NULL;
    char __iomem* gamma_base = NULL;

    hisifd = (struct hisi_fb_data_type*) pdata;

    if ( NULL == hisifd )
    {
        LCDKIT_ERR("NULL point!\n");
        return;
    }

    mipi_dsi0_base = hisifd->mipi_dsi0_base;
    dpp_base = hisifd->dss_base + DSS_DPP_OFFSET;
    lcp_base = hisifd->dss_base + DSS_DPP_LCP_OFFSET_ES;
    gamma_base = hisifd->dss_base + DSS_DPP_GAMA_OFFSET;

    pinfo = &(hisifd->panel_info);

    if (ctrl)
    {
        if (pinfo->gamma_support == 1){
            HISI_FB_INFO("disable gamma\n");
            /* disable de-gamma */
            set_reg(lcp_base + LCP_DEGAMA_EN_ES, 0x0, 1, 0);
            /* disable gamma */
            set_reg(gamma_base + GAMA_EN, 0x0, 1, 0);
        }
        if (pinfo->gmp_support == 1) {
            HISI_FB_INFO("disable gmp\n");
            /* disable gmp */
            set_reg(dpp_base + LCP_GMP_BYPASS_EN_ES, 0x1, 1, 0);
        }
        if (pinfo->xcc_support == 1) {
            HISI_FB_INFO("disable xcc\n");
            /* disable xcc */
            set_reg(lcp_base + LCP_XCC_BYPASS_EN_ES, 0x1, 1, 0);
        }
    } else {
        if (pinfo->gamma_support == 1) {
            HISI_FB_INFO("enable gamma\n");
            /* enable de-gamma */
            set_reg(lcp_base + LCP_DEGAMA_EN_ES, 0x1, 1, 0);
            /* enable gamma */
            set_reg(gamma_base + GAMA_EN, 0x1, 1, 0);
        }
        if (pinfo->gmp_support == 1) {
            HISI_FB_INFO("enable gmp\n");
            /* enable gmp */
            set_reg(dpp_base + LCP_GMP_BYPASS_EN_ES, 0x0, 1, 0);
        }
        if (pinfo->xcc_support == 1) {
            HISI_FB_INFO("enable xcc\n");
            /* enable xcc */
            set_reg(lcp_base + LCP_XCC_BYPASS_EN_ES, 0x0, 1, 0);
        }
    }
}
#else
void lcdkit_effect_switch_ctrl(void* pdata, bool ctrl)
{
    struct hisi_fb_data_type* hisifd = NULL;
    struct hisi_panel_info* pinfo = NULL;
    char __iomem* mipi_dsi0_base = NULL;
    char __iomem* dpp_base = NULL;
    char __iomem* lcp_base = NULL;
    char __iomem* gamma_base = NULL;

    hisifd = (struct hisi_fb_data_type*) pdata;

    if ( NULL == hisifd )
    {
        LCDKIT_ERR("NULL point!\n");
        return;
    }

    mipi_dsi0_base = hisifd->mipi_dsi0_base;
    dpp_base = hisifd->dss_base + DSS_DPP_OFFSET;
    lcp_base = hisifd->dss_base + DSS_DPP_LCP_OFFSET;
    gamma_base = hisifd->dss_base + DSS_DPP_GAMA_OFFSET;

    pinfo = &(hisifd->panel_info);

    if (ctrl)
    {
        if (pinfo->gamma_support == 1){
            HISI_FB_INFO("disable gamma\n");
            /* disable de-gamma */
            set_reg(lcp_base + LCP_DEGAMA_EN, 0x0, 1, 0);
            /* disable gamma */
            set_reg(gamma_base + GAMA_EN, 0x0, 1, 0);
        }
        if (pinfo->gmp_support == 1) {
            HISI_FB_INFO("disable gmp\n");
            /* disable gmp */
            set_reg(dpp_base + LCP_GMP_BYPASS_EN, 0x1, 1, 0);
        }
        if (pinfo->xcc_support == 1) {
            HISI_FB_INFO("disable xcc\n");
            /* disable xcc */
            set_reg(lcp_base + LCP_XCC_BYPASS_EN, 0x1, 1, 0);
        }

        /* disable bittext */
        set_reg(hisifd->dss_base + DSS_DPP_BITEXT0_OFFSET + BIT_EXT0_CTL, 0x0, 1, 0);
    } else {
        if (pinfo->gamma_support == 1) {
            HISI_FB_INFO("enable gamma\n");
            /* enable de-gamma */
            set_reg(lcp_base + LCP_DEGAMA_EN, 0x1, 1, 0);
            /* enable gamma */
            set_reg(gamma_base + GAMA_EN, 0x1, 1, 0);
        }
        if (pinfo->gmp_support == 1) {
            HISI_FB_INFO("enable gmp\n");
            /* enable gmp */
            set_reg(dpp_base + LCP_GMP_BYPASS_EN, 0x0, 1, 0);
        }
        if (pinfo->xcc_support == 1) {
            HISI_FB_INFO("enable xcc\n");
            /* enable xcc */
            set_reg(lcp_base + LCP_XCC_BYPASS_EN, 0x0, 1, 0);
        }
        /* enable bittext */
        set_reg(hisifd->dss_base + DSS_DPP_BITEXT0_OFFSET + BIT_EXT0_CTL, 0x1, 1, 0);
    }
}
#endif
int adc_get_value(int channel)
{
    // hisi_adc_get_value(channel);
    return 0;
}

int lcdkit_fake_update_bl(void *pdata, uint32_t bl_level)
{
    int ret = 0;
    struct hisi_fb_data_type *hisifd = NULL;
	struct platform_device lcdkit_pdev = {0};

    hisifd = (struct hisi_fb_data_type *)pdata;

    BUG_ON(hisifd == NULL);
	platform_set_drvdata(&lcdkit_pdev, hisifd);

    if (bl_level > 0) {
        /*enable bl gpio*/
//        if (bl_enable_flag) {
//            gpio_direction_output(gpio_lcd_bl_enable, 1);
//        }
        mdelay(2);
        /* backlight on */
        hisi_lcd_backlight_on(&lcdkit_pdev);

        HISI_FB_INFO("set backlight to %d\n", bl_level);
        ret = hisi_blpwm_set_backlight(hisifd, bl_level);
    } else {
        ret = hisi_blpwm_set_backlight(hisifd, 0);
        /* backlight off */
        hisi_lcd_backlight_off(&lcdkit_pdev);
        /*disable bl gpio*/
//        if (bl_enable_flag) {
//            gpio_direction_output(gpio_lcd_bl_enable, 0);
//        }
    }
	return ret;
}

int buf_trans(const char* inbuf, int inlen, char** outbuf, int* outlen)
{
    char* buf;
    int i;
    int bufsize = inlen;

    if (!inbuf)
    {
        LCDKIT_ERR("inbuf is null point!\n");
        return -ENOMEM;
    }

    /*The property is 4bytes long per element in cells: <>*/
    bufsize = bufsize / 4;
    /*If use bype property: [], this division should be removed*/
    buf = kzalloc(sizeof(char) * bufsize, GFP_KERNEL);

    if (!buf)
    {
        LCDKIT_ERR("buf is null point!\n");
        return -ENOMEM;
    }

    //For use cells property: <>
    for (i = 0; i < bufsize; i++)
    {
        buf[i] = inbuf[i * 4 + 3];
    }

    *outbuf = buf;
    *outlen = bufsize;

    return 0;
}

int lcdkit_check_mipi_fifo_empty(char __iomem *dsi_base)
{
    unsigned long dw_jiffies = 0;
    uint32_t pkg_status = 0;
    uint32_t phy_status = 0;
    int is_timeout = 1;

    /*read status register*/
    dw_jiffies = jiffies + HZ;
    do {
        pkg_status = inp32(dsi_base + MIPIDSI_CMD_PKT_STATUS_OFFSET);
        phy_status = inp32(dsi_base + MIPIDSI_PHY_STATUS_OFFSET);
        if ((pkg_status & 0x1) == 0x1 && !(phy_status & 0x2)){
            is_timeout = 0;
            break;
        }
    } while (time_after(dw_jiffies, jiffies));

    if (is_timeout) {
        HISI_FB_ERR("mipi check empty fail: \n \
            MIPIDSI_CMD_PKT_STATUS = 0x%x \n \
            MIPIDSI_PHY_STATUS = 0x%x \n \
            MIPIDSI_INT_ST1_OFFSET = 0x%x \n",
            inp32(dsi_base + MIPIDSI_CMD_PKT_STATUS_OFFSET),
            inp32(dsi_base + MIPIDSI_PHY_STATUS_OFFSET),
            inp32(dsi_base + MIPIDSI_INT_ST1_OFFSET));
        return -1;
    }
    return 0;
}

void lcdkit_fps_scence_adaptor_handle(struct platform_device* pdev, uint32_t scence)
{
    struct hisi_fb_data_type *hisifd = NULL;
    struct hisi_panel_info *pinfo = NULL;

    LCDKIT_DEBUG("+.\n");
    if (NULL == pdev) {
        LCDKIT_ERR("pdev NULL Pointer!\n");
        return;
    }
    hisifd = platform_get_drvdata(pdev);
    if (NULL == hisifd){
        LCDKIT_ERR("hisifd NULL Pointer!\n");
        return;
    }
    pinfo = &(hisifd->panel_info);
    switch (scence)
    {
        case LCD_FPS_SCENCE_NORMAL:
            pinfo->fps_updt = LCD_FPS_60;
            LCDKIT_DEBUG("scence is LCD_FPS_SCENCE_NORMAL, framerate is 60fps!\n");
            break;

        case LCD_FPS_SCENCE_IDLE:
            pinfo->fps_updt = LCD_FPS_30;
            LCDKIT_DEBUG("scence is LCD_FPS_SCENCE_IDLE, framerate is 30fps!\n");
            break;

        /*
        * Open dss dynamic fps function, dss 30fps, panel 30fps, 
        * and dfr closed if panel support
        */
        case LCD_FPS_SCENCE_FORCE_30FPS:
            LCDKIT_INFO("scence is  LCD_FPS_SCENCE_FORCE_30FPS\n");
            pinfo->fps_updt_support = 1;
            pinfo->fps_updt_panel_only = 1;
            pinfo->fps_updt = LCD_FPS_30;
            pinfo->fps_updt_force_update = 1;
            pinfo->fps_scence = scence;
            break;
        /*
        * Open dss dynamic fps function, dss 30<->60,
        * panel 60fps, and dfr open if panel support
        */
        case LCD_FPS_SCENCE_FUNC_DEFAULT_ENABLE:
            LCDKIT_INFO("scence is  LCD_FPS_SCENCE_FUNC_DEFAULT_ENABLE\n");
            pinfo->fps_updt_support = 1;
            pinfo->fps_updt_panel_only = 0;
            pinfo->fps_updt = LCD_FPS_60;
            pinfo->fps_updt_force_update = 1;
            pinfo->fps_scence = scence;
            break;
        /*
        * Close dss dynamic fps function, dss 60fps, panel 60fps,
        * and dfr closed if panel support
        */
        case LCD_FPS_SCENCE_FUNC_DEFAULT_DISABLE:
            LCDKIT_INFO("scence is  LCD_FPS_SCENCE_FUNC_DEFAULT_DISABLE\n");
            pinfo->fps_updt_force_update = 1;
            pinfo->fps_updt = LCD_FPS_60;
            pinfo->fps_scence = scence;
            break;

        default:
            pinfo->fps_updt = LCD_FPS_60;
            LCDKIT_INFO("scence is LCD_FPS_SCENCE_NORMAL, framerate is 60fps!\n");
            break;
    }

    LCDKIT_DEBUG("-.\n");
    return;
}

void lcdkit_fps_scence_switch_immediately(struct platform_device *pdev, uint32_t scence)
{
    struct hisi_fb_data_type* hisifd = NULL;
    struct hisi_panel_info *pinfo = NULL;

    LCDKIT_DEBUG("+.\n");
    if (NULL == pdev)
    {
        LCDKIT_ERR("pdev NULL Pointer!\n");
        return;
    }

    hisifd = platform_get_drvdata(pdev);
    if (NULL == hisifd){
        LCDKIT_ERR("hisifd NULL Pointer!\n");
        return;
    }
    pinfo = &(hisifd->panel_info);

    down(&hisifd->blank_sem);
    hisifb_activate_vsync(hisifd);
    if (lcdkit_check_mipi_fifo_empty(hisifd->mipi_dsi0_base))
        goto out;
    if (LCDKIT_DSI_LP_MODE
        == lcdkit_info.panel_infos.dfr_enable_cmds.link_state)
        lcdkit_hs_lp_switch(hisifd, LCDKIT_DSI_LP_MODE);
    switch (scence)
    {
        case LCD_FPS_SCENCE_FUNC_DEFAULT_ENABLE:
            lcdkit_dsi_tx(hisifd, &lcdkit_info.panel_infos.dfr_enable_cmds);
            pinfo->fps_updt_support = 1;
            pinfo->fps_scence = LCD_FPS_SCENCE_FUNC_DEFAULT_ENABLE;
            break;
        case LCD_FPS_SCENCE_FUNC_DEFAULT_DISABLE:
            lcdkit_dsi_tx(hisifd, &lcdkit_info.panel_infos.fps_to_60_cmds);
            pinfo->fps_updt_support = 0;
            pinfo->fps_scence = LCD_FPS_SCENCE_FUNC_DEFAULT_DISABLE;
            break;
        default:
            break;
    }
    if (LCDKIT_DSI_LP_MODE
        == lcdkit_info.panel_infos.dfr_enable_cmds.link_state)
        lcdkit_hs_lp_switch(hisifd, LCDKIT_DSI_HS_MODE);

    pinfo->fps_updt_panel_only = 0;
    pinfo->fps_updt = LCD_FPS_60;

    if (lcdkit_check_mipi_fifo_empty(hisifd->mipi_dsi0_base))
        goto out;
    LCDKIT_DEBUG("switch to scence %d immediately\n", scence);
out:
    hisifb_deactivate_vsync(hisifd);
    up(&hisifd->blank_sem);
    LCDKIT_DEBUG("-.\n");
    return ;
}

static void lcdkit_fps_work_handler(struct work_struct *data)
{
    struct platform_device *pdev = NULL;
    struct hisi_fb_data_type* hisifd = NULL;
    struct hisi_panel_info *pinfo = NULL;

    LCDKIT_DEBUG("+.\n");
    lcdkit_get_pdev(&pdev);
    if (NULL == pdev)
    {
        LCDKIT_ERR("pdev NULL Pointer!\n");
        return;
    }

    hisifd = platform_get_drvdata(pdev);
    if (NULL == hisifd){
        LCDKIT_ERR("hisifd NULL Pointer!\n");
        return;
    }
    pinfo = &(hisifd->panel_info);
    if (!hisifd->panel_power_on)
    {
        LCDKIT_ERR("panel power off!\n");
        return ;
    }
    if (LCD_FPS_SCENCE_FUNC_DEFAULT_ENABLE == pinfo->fps_scence)
    {
        LCDKIT_DEBUG("panel not disable dfr, no need to switch\n");
        return  ;
    }

    LCDKIT_DEBUG("%s fps to 60 and enable dfr\n", __func__);
    lcdkit_fps_scence_switch_immediately(pdev, LCD_FPS_SCENCE_FUNC_DEFAULT_ENABLE);
    LCDKIT_DEBUG("-.\n");
}

void lcdkit_fps_timer_adaptor_handler(unsigned long data)
{
    LCDKIT_DEBUG("+.\n");
    if (lcdkit_info.panel_infos.fps_scence_wq)
        queue_work(lcdkit_info.panel_infos.fps_scence_wq,
            &lcdkit_info.panel_infos.fps_scence_work);
    LCDKIT_DEBUG("-.\n");
    return ;
}

void lcdkit_fps_timer_adaptor_init(void)
{
        init_timer(&lcdkit_info.panel_infos.fps_scence_timer);
        lcdkit_info.panel_infos.fps_scence_timer.data = 0;
        lcdkit_info.panel_infos.fps_scence_timer.expires = jiffies + HZ;
        lcdkit_info.panel_infos.fps_scence_timer.function = lcdkit_fps_timer_adaptor_handler;

        lcdkit_info.panel_infos.fps_scence_wq = create_singlethread_workqueue("fps_wq");
        if (!lcdkit_info.panel_infos.fps_scence_wq)
        {
            LCDKIT_ERR("fps workqueue create fail!!\n");
        }
        else
        {
            INIT_WORK(&lcdkit_info.panel_infos.fps_scence_work, lcdkit_fps_work_handler);
        }
        return ;
}

void lcdkit_fps_adaptor_ts_callback(void)
{
    struct platform_device *pdev = NULL;
    struct hisi_fb_data_type* hisifd = NULL;
    struct hisi_panel_info *pinfo = NULL;

    LCDKIT_DEBUG("%s+\n", __func__);
    lcdkit_get_pdev(&pdev);
    if (NULL == pdev)
    {
        LCDKIT_ERR("pdev NULL Pointer!\n");
        return;
    }

    hisifd = platform_get_drvdata(pdev);
    if (NULL == hisifd){
        LCDKIT_ERR("hisifd NULL Pointer!\n");
        return;
    }
    pinfo = &(hisifd->panel_info);
    if (!hisifd->panel_power_on)
    {
        LCDKIT_ERR("panel power off!\n");
        return ;
    }
    if (LCD_FPS_SCENCE_FUNC_DEFAULT_ENABLE != pinfo->fps_scence)
    {
        LCDKIT_DEBUG("panel not enable dfr, no need to switch\n");
        mod_timer(&lcdkit_info.panel_infos.fps_scence_timer, jiffies + HZ);
        return ;
    }

    LCDKIT_DEBUG("%s fps to 60 and disable dfr\n", __func__);
    lcdkit_fps_scence_switch_immediately(pdev, LCD_FPS_SCENCE_FUNC_DEFAULT_DISABLE);

    mod_timer(&lcdkit_info.panel_infos.fps_scence_timer, jiffies + HZ);
    LCDKIT_DEBUG("%s-\n", __func__);
    return ;
}

void lcdkit_fps_updt_adaptor_handle(void* pdata)
{
    struct hisi_fb_data_type* hisifd = NULL;
    struct hisi_panel_info *pinfo = NULL;
    struct platform_device *pdev = NULL;

    pdev = (struct platform_device *)pdata;
    if (NULL == pdev) {
        LCDKIT_ERR("pdev NULL Pointer!\n");
        return;
    }

    hisifd = platform_get_drvdata(pdev);
    if (NULL == hisifd){
        LCDKIT_ERR("hisifd NULL Pointer!\n");
        return;
    }

    pinfo = &(hisifd->panel_info);
    switch(pinfo->fps_scence)
    {
        /* USE fps_to_60_cmds for one cmd */
        case LCD_FPS_SCENCE_FUNC_DEFAULT_DISABLE:
            LCDKIT_INFO("fps to 60 and disable dfr\n");
            if (LCDKIT_DSI_LP_MODE
                == lcdkit_info.panel_infos.fps_to_60_cmds.link_state)
                lcdkit_hs_lp_switch(hisifd, LCDKIT_DSI_LP_MODE);
            lcdkit_dsi_tx(hisifd, &lcdkit_info.panel_infos.fps_to_60_cmds);
            if (LCDKIT_DSI_LP_MODE
                == lcdkit_info.panel_infos.fps_to_60_cmds.link_state)
                lcdkit_hs_lp_switch(hisifd, LCDKIT_DSI_HS_MODE);

            LCDKIT_INFO("set fps_updt_support = 0, fps_updt_panel_only = 0\n");
            pinfo->fps_updt_support = 0;
            pinfo->fps_updt_panel_only = 0;
            break;
        /* USE dfr_enable_cmds for one cmd */
        case LCD_FPS_SCENCE_FUNC_DEFAULT_ENABLE:
            LCDKIT_INFO("fps to 60 and enable dfr\n");
            if (LCDKIT_DSI_LP_MODE
                == lcdkit_info.panel_infos.dfr_enable_cmds.link_state)
                lcdkit_hs_lp_switch(hisifd, LCDKIT_DSI_LP_MODE);
            lcdkit_dsi_tx(hisifd, &lcdkit_info.panel_infos.dfr_enable_cmds);
            if (LCDKIT_DSI_LP_MODE
                == lcdkit_info.panel_infos.dfr_enable_cmds.link_state)
                lcdkit_hs_lp_switch(hisifd, LCDKIT_DSI_HS_MODE);
            break;
        /* USE fps_to_30_cmds for one cmd */
        case LCD_FPS_SCENCE_FORCE_30FPS:
            LCDKIT_INFO("fps to 30 and disable dfr\n");
            if (LCDKIT_DSI_LP_MODE
                == lcdkit_info.panel_infos.fps_to_30_cmds.link_state)
                lcdkit_hs_lp_switch(hisifd, LCDKIT_DSI_LP_MODE);
            lcdkit_dsi_tx(hisifd, &lcdkit_info.panel_infos.fps_to_30_cmds);
            if (LCDKIT_DSI_LP_MODE
                == lcdkit_info.panel_infos.fps_to_30_cmds.link_state)
                lcdkit_hs_lp_switch(hisifd, LCDKIT_DSI_HS_MODE);
            break;
        default:
            LCDKIT_INFO("unknown scence:%d\n", pinfo->fps_scence);
            break;
    }

    if (pinfo->fps_updt_force_update)
    {
        LCDKIT_INFO("set fps_updt_force_update = 0\n");
        pinfo->fps_updt_force_update = 0;
    }
    return;
}
int lcdkit_lread_reg(void *pdata, uint32_t *out, struct lcdkit_dsi_cmd_desc* cmds, uint32_t len)
{
	int ret = 0;
	struct dsi_cmd_desc lcd_reg_cmd;
	struct hisi_fb_data_type* hisifd = NULL;
	hisifd = (struct hisi_fb_data_type*) pdata;
	lcd_reg_cmd.dtype = cmds->dtype;
	lcd_reg_cmd.vc = cmds->vc;
	lcd_reg_cmd.wait = cmds->wait;
	lcd_reg_cmd.waittype = cmds->waittype;
	lcd_reg_cmd.dlen = cmds->dlen;
	lcd_reg_cmd.payload = cmds->payload;
	ret = mipi_dsi_lread_reg(out, &lcd_reg_cmd, len, hisifd->mipi_dsi0_base);
	if (ret) {
		LCDKIT_INFO("read error, ret=%d\n", ret);
		return ret;
	}
	return ret;
}

static unsigned char ddic_oem_type = 0;
static uint8_t lcd_write_flag = 0;
static unsigned char cmd_ddic_oem_info[LCD_OEM_INFO_LEN] = { 0 };
#ifdef CONFIG_JDI_HOST_TS_KIT
static char cmd_tpic_oem_info[TP_OEM_INFO_LEN + 1] = {0};
#endif
static int __init early_parse_ddic_oem_cmdline(char *arg)
{
	int len = 0;
	memset(cmd_ddic_oem_info, 0, sizeof(cmd_ddic_oem_info));
	if (arg) {
		len = strlen(arg);
		if (len > sizeof(cmd_ddic_oem_info)) {
			len = sizeof(cmd_ddic_oem_info);
		}
		memcpy(cmd_ddic_oem_info, arg, len);
	} else {
		LCDKIT_ERR("arg is NULL\n");
	}

	return 0;
}

early_param("DDIC_INFO", early_parse_ddic_oem_cmdline);

static int hostprocessing_read_ddic(uint8_t *out, struct lcdkit_dsi_panel_cmds *cmds, struct hisi_fb_data_type *hisifd)
{
	int i = 0, ret = 0, dlen = 0, cnt = 0;
	struct lcdkit_dsi_cmd_desc *cm;
	uint32_t tmp_value[LCD_DDIC_INFO_LEN] = {0};

	cm = cmds->cmds;
	for (i = 0; i < cmds->cmd_cnt; i++) {
		ret = lcdkit_lread_reg(hisifd, tmp_value, cm, cm->dlen);
		if (ret) {
			LCDKIT_ERR("read reg error\n");
			return ret;
		}
		for (dlen = 0; dlen < cm->dlen; dlen++) {
			switch (dlen % 4) {
			case 0:
				if ((tmp_value[dlen / 4] & 0xFF) == 0) {
					out[cnt] = (uint8_t)((tmp_value[dlen / 4] & 0xFF) + '0');
				} else {
					out[cnt] = (uint8_t)(tmp_value[dlen / 4] & 0xFF);
				}
				break;
			case 1:
				if (((tmp_value[dlen / 4] >> 8) & 0xFF) == 0) {
					out[cnt] = (uint8_t)(((tmp_value[dlen / 4] >> 8) & 0xFF) + '0');
				} else {
					out[cnt] = (uint8_t)((tmp_value[dlen / 4] >> 8) & 0xFF);
				}
				break;
			case 2:
				if (((tmp_value[dlen / 4] >> 16) & 0xFF) == 0) {
					out[cnt] = (uint8_t)(((tmp_value[dlen / 4] >> 16) & 0xFF) + '0');
				} else {
					out[cnt] = (uint8_t)((tmp_value[dlen / 4] >> 16) & 0xFF);
				}
				break;
			case 3:
				if (((tmp_value[dlen / 4] >> 24) & 0xFF) == 0) {
					out[cnt] = (uint8_t)(((tmp_value[dlen / 4] >> 24) & 0xFF) + '0');
				} else {
					out[cnt] = (uint8_t)((tmp_value[dlen / 4] >> 24) & 0xFF);
				}
				break;
			default:
				break;
			}
			cnt++;
		}
		cm++;
	}
	return 0;
}

int hostprocessing_get_project_id(char *out)
{
	int i = 0;
	int ret = 0;
	struct hisi_fb_data_type *hisifd_primary = NULL;
	uint8_t read_value[LCD_DDIC_INFO_LEN] = {0};

	hisifd_primary = hisifd_list[PRIMARY_PANEL_IDX];
	if ((NULL == hisifd_primary) || (NULL == out)) {
		LCDKIT_ERR("NULL pointer\n");
		return -1;
	}

	if (lcdkit_info.panel_infos.host_info_all_in_ddic) {
		lcdkit_dsi_tx(hisifd_primary, &lcdkit_info.panel_infos.host_project_id_enter_cmds);
		ret = hostprocessing_read_ddic(read_value, &lcdkit_info.panel_infos.host_project_id_cmds, hisifd_primary);
		lcdkit_dsi_tx(hisifd_primary, &lcdkit_info.panel_infos.host_project_id_exit_cmds);
		if (ret) {
			LCDKIT_ERR("read error\n");
			return -1;
		}
		for (i = 0; i < DDIC_PRODUCT_ID_OFFSET; i++) {
			out[i] = read_value[i];
		}
		LCDKIT_INFO("host project id end[info all in ddic]!\n");
		return ret;
	}

	for (i = 0; i < DDIC_PRODUCT_ID_OFFSET; i ++) {
		out[i] = cmd_ddic_oem_info[i];
	}
	LCDKIT_INFO("host project id end[info part in ddic]!\n");
	return ret;
}

static void hostprocessing_get_ddic_product_id(char *oem_data, struct hisi_fb_data_type *hisifd)
{
	uint8_t i = 0;
	uint8_t read_value[LCD_DDIC_INFO_LEN] = {0};

	if ((NULL == hisifd) || (NULL == oem_data)) {
		LCDKIT_ERR("NULL pointer\n");
		return;
	}

	oem_data[0] = HOST_OEM_PRODUCT_ID_TYPE;
	oem_data[1] = LCD_OEM_BLOCK_NUM;

	if (lcdkit_info.panel_infos.host_info_all_in_ddic) {
		lcdkit_dsi_tx(hisifd, &lcdkit_info.panel_infos.host_project_id_enter_cmds);
		hostprocessing_read_ddic(read_value, &lcdkit_info.panel_infos.host_project_id_cmds, hisifd);
		lcdkit_dsi_tx(hisifd, &lcdkit_info.panel_infos.host_project_id_exit_cmds);
		for (i = 0; i < DDIC_PRODUCT_ID_OFFSET; i++) {
			oem_data[i + 2] = read_value[i];
		}
		LCDKIT_INFO("host project id end!\n");
		return ;
	}

	for (i = 0; i < DDIC_PRODUCT_ID_OFFSET; i ++) {
		oem_data[i+2] = cmd_ddic_oem_info[i];
	}

	LCDKIT_INFO("finished\n");
}

static void hostprocessing_get_2d_barcode(char *oem_data,struct hisi_fb_data_type *hisifd)
{
	uint8_t i = 0;
	uint8_t read_value[LCD_DDIC_INFO_LEN] = {0};

	if ((NULL == hisifd) || (NULL == oem_data)) {
		LCDKIT_ERR("NULL pointer\n");
		return;
	}
	for (i = 0; i < LCD_OEM_2DBLOCK_NUM*LCD_OEM_BLOCK_LEN; i ++) {
		oem_data[i] = 0;
	}

	oem_data[0] = HOST_OEM_2D_BARCODE_TYPE;
	oem_data[1] = LCD_OEM_2DBLOCK_NUM;

	if (lcdkit_info.panel_infos.host_info_all_in_ddic) {

		lcdkit_dsi_tx(hisifd, &lcdkit_info.panel_infos.host_2d_barcode_enter_cmds);
		hostprocessing_read_ddic(read_value, &lcdkit_info.panel_infos.host_2d_barcode_cmds, hisifd);
		lcdkit_dsi_tx(hisifd, &lcdkit_info.panel_infos.host_2d_barcode_exit_cmds);
		for (i = 0; i < LCD_OEM_2DBLOCK_NUM*LCD_OEM_BLOCK_LEN - 2; i++) {
			oem_data[i + 2] = read_value[i];
		}
		LCDKIT_INFO("host 2d barcode end!\n");
		return ;
	}
#ifdef CONFIG_JDI_HOST_TS_KIT
	bu21150_otp_read(cmd_tpic_oem_info);
#endif

	for (i = 0; i < DDIC_HW_PART_NUM_OFFSET; i ++) {
		oem_data[i+2] = cmd_ddic_oem_info[i+DDIC_PRODUCT_ID_OFFSET];
	}

#ifdef CONFIG_JDI_HOST_TS_KIT
	oem_data[11] = cmd_tpic_oem_info[0];//rework info
#endif
	oem_data[12] = cmd_ddic_oem_info[19];//Module manufacturing place
#ifdef CONFIG_JDI_HOST_TS_KIT
	oem_data[13] = cmd_tpic_oem_info[1];//Module manufacturing date
	oem_data[14] = cmd_tpic_oem_info[2];
	oem_data[15] = cmd_tpic_oem_info[3];
	oem_data[16] = cmd_tpic_oem_info[4];//Serial Number
	oem_data[17] = cmd_tpic_oem_info[5];
	oem_data[18] = cmd_tpic_oem_info[6];
	oem_data[19] = cmd_tpic_oem_info[7];
	oem_data[20] = cmd_tpic_oem_info[8];//PNL manufacturing palce
	oem_data[21] = cmd_tpic_oem_info[9];//panel manufacturing date
	oem_data[22] = cmd_tpic_oem_info[10];
	oem_data[23] = cmd_tpic_oem_info[11];
#endif
	oem_data[24] = cmd_ddic_oem_info[20];
	oem_data[25] = cmd_ddic_oem_info[21];
	oem_data[26] = cmd_ddic_oem_info[22];
	oem_data[27] = cmd_ddic_oem_info[23];
#ifdef CONFIG_JDI_HOST_TS_KIT
	oem_data[31] = cmd_tpic_oem_info[12];//TP IC manufacturing date
	oem_data[32] = cmd_tpic_oem_info[13];
	oem_data[33] = cmd_tpic_oem_info[14];
	oem_data[34] = cmd_ddic_oem_info[24];
#endif
	oem_data[38] = cmd_ddic_oem_info[25];
	oem_data[42] = cmd_ddic_oem_info[26];
	oem_data[43] = cmd_ddic_oem_info[27];
	oem_data[44] = cmd_ddic_oem_info[28];
	oem_data[45] = cmd_ddic_oem_info[29];
	oem_data[46] = cmd_ddic_oem_info[30];
	oem_data[47] = cmd_ddic_oem_info[31];

	LCDKIT_INFO("finished\n");
}

static void hostprocessing_read_wc(uint32_t *read_data, struct hisi_fb_data_type *hisifd)
{
	uint32_t read_value[2] = {0};
	int read_ret = 0;
	int i = 0;

	if ((NULL == hisifd) || (NULL == read_data)) {
		LCDKIT_ERR("NULL pointer\n");
		return;
	}

	static char color_white_a1[] = {0xa1};
	struct dsi_cmd_desc color_white_reg[] = {
		{DTYPE_GEN_READ1, 0, 10, WAIT_TYPE_US,
			sizeof(color_white_a1), color_white_a1},
	};

	char __iomem *mipi_dsi0_base = NULL;

	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	read_ret = mipi_dsi_lread_reg(read_value, color_white_reg, LCD_WHITECOLOR_LEN, (char *)(unsigned long)mipi_dsi0_base);
	if (read_ret) {
		LCDKIT_INFO("read error, ret=%d\n", read_ret);
	}
	for (i = 0; i < (LCD_WHITECOLOR_LEN + 3) / 4; i++) {
		read_data[i] = read_value[i];
	}
}

static void hostprocessing_get_brightness(char *oem_data, struct hisi_fb_data_type *hisifd)
{
	uint32_t read_value[2] = {0};

	if ((NULL == hisifd) || (NULL == oem_data)) {
		LCDKIT_ERR("NULL pointer\n");
		return;
	}

	hostprocessing_read_wc(read_value, hisifd);

	oem_data[0] = HOST_OEM_BRIGHTNESS_TYPE;
	oem_data[1] = LCD_OEM_BLOCK_NUM;
	oem_data[2] = (uint8_t)(read_value[0]&0xff);//brightness low byte
	oem_data[3] = (uint8_t)((read_value[0]>>8)&0xff);//brightness high byte

	LCDKIT_INFO("finished\n");
}

static void hostprocessing_get_colorpoint_of_white(char *oem_data ,struct hisi_fb_data_type *hisifd)
{
	//ddic get color point data 4bytes
	uint32_t read_value[2] = {0};

	if ((NULL == hisifd) || (NULL == oem_data)) {
		LCDKIT_ERR("NULL pointer\n");
		return;
	}

	hostprocessing_read_wc(read_value, hisifd);

	oem_data[0] = HOST_OEM_COLOROFWHITE_TYPE;
	oem_data[1] = LCD_OEM_BLOCK_NUM;
	oem_data[2] = (uint8_t)((read_value[0]>>16)&0xff);//x low byte
	oem_data[3] = (uint8_t)((read_value[0]>>24)&0xff);//x high byte
	oem_data[4] = (uint8_t)(read_value[1]&0xff);//y low byte
	oem_data[5] = (uint8_t)((read_value[1]>>8)&0xff);//y high byte

	LCDKIT_INFO("finished\n");
}

static void hostprocessing_get_bright_colorpoint_of_white(char *oem_data, struct hisi_fb_data_type *hisifd)
{
	//ddic get bright and color of white data 6bytes
	uint32_t read_value[2] = {0};

	if ((NULL == hisifd) || (NULL == oem_data)) {
		LCDKIT_ERR("NULL pointer\n");
		return;
	}

	hostprocessing_read_wc(read_value, hisifd);

	oem_data[0] = HOST_OEM_BRIGHTNESSANDCOLOR_TYPE;
	oem_data[1] = LCD_OEM_BLOCK_NUM;
	oem_data[2] = (uint8_t)(read_value[0]&0xff);//brightness low byte
	oem_data[3] = (uint8_t)((read_value[0]>>8)&0xff);//brightness high byte
	oem_data[4] = (uint8_t)((read_value[0]>>16)&0xff);//x low byte
	oem_data[5] = (uint8_t)((read_value[0]>>24)&0xff);//x high byte
	oem_data[6] = (uint8_t)(read_value[1]&0xff);//y low byte
	oem_data[7] = (uint8_t)((read_value[1]>>8)&0xff);//y high byte

	LCDKIT_INFO("finished\n");
}

static void hostprocessing_get_rework(char *oem_data, struct hisi_fb_data_type *hisifd)
{
	if ((NULL == hisifd) || (NULL == oem_data)) {
		LCDKIT_ERR("NULL pointer\n");
		return;
	}

	oem_data[0] = HOST_OEM_REWORK_TYPE;
	oem_data[1] = LCD_OEM_BLOCK_NUM;
	oem_data[2] = 0x0;

	LCDKIT_INFO("finished\n");
}

static void hostprocessing_set_bright_colorpoint_of_white(char *oem_data, struct hisi_fb_data_type *hisifd)
{
	//ddic get bright and color of white data 6bytes
	//the data format is :0x04,0x01,brightness low byte, brightness high byte,cxl,cxh,cyl,cyh
	char __iomem *mipi_dsi0_base = NULL;
	struct hisi_panel_info *pinfo = NULL;

	if ((NULL == hisifd) || (NULL == oem_data)) {
		LCDKIT_ERR("NULL pointer\n");
		return;
	}

	pinfo = &(hisifd->panel_info);
	mipi_dsi0_base = hisifd->mipi_dsi0_base;
	uint32_t read_value[1] = {0};
	int error = 0;
	int i = 0;

	for (i = 0; i < LCD_OEM_BLOCK_LEN; i ++) {
		LCDKIT_INFO("the %d write data is %x\n", i, oem_data[i]);
	}

	char lcd_manu_protect_off[] = {0xff,0x20};//manufacture command access
	char lcd_nvm_load_setting[] = {0xfb,0x01};
	char lcd_read_finish_reg[] = {0xff,0x10};//wait >=10ms
	char display_off[] = {0x28};//set lcd_display_off, wait >=10ms
	char lcd_page_select[] = {0xff,0x20};
	char lcd_mtp_zone_sel[] = {0x3f,0x01};
	char lcd_enable_mtp[] = {0x39,0x10};
	char lcd_init_mtp_flow[] = {0x38,0x01};	//wait >=50ms
	static char lcd_enable_inter_power[] = {0x39,0x10};	//wait >=120ms
	char lcd_enable_mtp_wr[] = {0x3d,0x01};
	char lcd_ewrite_1[] = {0x40,0x55};
	char lcd_ewrite_2[] = {0x41,0xaa};
	char lcd_ewrite_3[] = {0x42,0x66};
	char lcd_flag_status[] = {0x47};//0x14 read, 0x01 is ok,0x00 is NG, wait >=2000ms
	char lcd_dis_mtp_wr[] = {0x3d,0x00};

	struct dsi_cmd_desc lcd_write_bright_common[] = {
		{DTYPE_GEN_LWRITE, 0, 15, WAIT_TYPE_MS,
			sizeof(lcd_nvm_load_setting), lcd_nvm_load_setting},
		{DTYPE_GEN_LWRITE, 0, 12, WAIT_TYPE_MS,
			sizeof(lcd_read_finish_reg), lcd_read_finish_reg},
		{DTYPE_DCS_LWRITE, 0, 60, WAIT_TYPE_MS,
			sizeof(display_off), display_off},
		{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_page_select), lcd_page_select},
		{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
				sizeof(lcd_mtp_zone_sel), lcd_mtp_zone_sel},
		{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
				sizeof(lcd_enable_mtp), lcd_enable_mtp},
		{DTYPE_GEN_LWRITE, 0, 55, WAIT_TYPE_MS,
			sizeof(lcd_init_mtp_flow), lcd_init_mtp_flow},
		{DTYPE_GEN_LWRITE, 0, 125, WAIT_TYPE_MS,
			sizeof(lcd_enable_inter_power), lcd_enable_inter_power},
		{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_enable_mtp_wr), lcd_enable_mtp_wr},
		{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_ewrite_1), lcd_ewrite_1},
		{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_ewrite_2), lcd_ewrite_2},
		{DTYPE_GEN_LWRITE, 0, 12, WAIT_TYPE_MS,
			sizeof(lcd_ewrite_3), lcd_ewrite_3},
	};

	struct dsi_cmd_desc lcd_write_check[] = {
		{DTYPE_GEN_READ1, 0, 200, WAIT_TYPE_MS,
			sizeof(lcd_flag_status), lcd_flag_status},
	};

	struct dsi_cmd_desc lcd_dis_mtp_write[] = {
		{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_dis_mtp_wr), lcd_dis_mtp_wr},
	};

	//brightness
	char lcd_brightness_l[2] = {0x23,0x00};//brightness
	lcd_brightness_l[1] = oem_data[2];
	char lcd_brightness_h[2] = {0x24,0x00};//brightness
	lcd_brightness_h[1] = oem_data[3];

	//color point of white
	char lcd_color_of_white_xl[2] = {0x25,0x00};
	lcd_color_of_white_xl[1] = oem_data[4];//color point of white x low byte
	char lcd_color_of_white_xh[2] = {0x26,0x00};
	lcd_color_of_white_xh[1] = oem_data[5];//color point of white x high byte
	char lcd_color_of_white_y_l[2] = {0x27,0x00};//brightness
	lcd_color_of_white_y_l[1] = oem_data[6]; //color point for white y low byte
	char lcd_color_of_white_y_h[2] = {0x28,0x00};//brightness
	lcd_color_of_white_y_h[1] = oem_data[7]; //color point for white y high byte

	struct dsi_cmd_desc lcd_write_bright_cmd1[] = {
		{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_manu_protect_off), lcd_manu_protect_off},
		{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
				sizeof(lcd_brightness_l), lcd_brightness_l},
		{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
				sizeof(lcd_brightness_h), lcd_brightness_h},
		{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_color_of_white_xl), lcd_color_of_white_xl},
		{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_color_of_white_xh), lcd_color_of_white_xh},
		{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_color_of_white_y_l), lcd_color_of_white_y_l},
		{DTYPE_GEN_LWRITE, 0, 10, WAIT_TYPE_US,
			sizeof(lcd_color_of_white_y_h), lcd_color_of_white_y_h},
	};

	//write brightness data
	mipi_dsi_cmds_tx(lcd_write_bright_cmd1, \
		ARRAY_SIZE(lcd_write_bright_cmd1), mipi_dsi0_base);
	mipi_dsi_cmds_tx(lcd_write_bright_common, \
		ARRAY_SIZE(lcd_write_bright_common), mipi_dsi0_base);

	//read the flag status
	error = mipi_dsi_cmds_rx(read_value, lcd_write_check, ARRAY_SIZE(lcd_write_check), mipi_dsi0_base);
	if (error) {
		lcd_write_flag = 0;
		LCDKIT_INFO("panel_info write lcd ddic failed!\n");
	} else {
		lcd_write_flag = 1;
	}
	LCDKIT_INFO("%s lcd_write_check status %d finished\n", __func__, read_value[0]);

	mipi_dsi_cmds_tx(lcd_dis_mtp_write, \
		ARRAY_SIZE(lcd_dis_mtp_write), mipi_dsi0_base);

	LCDKIT_INFO("finished\n");
}

static uint8_t lcd_brightness[2] = {0};
static uint8_t lcd_colorpoint_of_white[4] = {0};
static void hostprocessing_set_brightness(char *oem_data, struct hisi_fb_data_type *hisifd)
{
	//ddic set bright data 2bytes,  data format is :0x02,0x01,brightness low byte, brightness high byte
	char __iomem *mipi_dsi0_base = NULL;

	if ((NULL == hisifd) || (NULL == oem_data)) {
		LCDKIT_ERR("NULL pointer\n");
		return;
	}

	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	lcd_brightness[0] = oem_data[2];
	lcd_brightness[1] = oem_data[3];
	if (lcd_write_flag == 1) {
		oem_data[4] = lcd_colorpoint_of_white[0];
		oem_data[5] = lcd_colorpoint_of_white[1];
		oem_data[6] = lcd_colorpoint_of_white[2];
		oem_data[7] = lcd_colorpoint_of_white[3];
	} else {
		oem_data[4] = (cmd_ddic_oem_info[36] - 48 ) * 16 + (cmd_ddic_oem_info[37] - 48);//x low byte sub 48 is for char to num
		oem_data[5] = (cmd_ddic_oem_info[38] - 48 ) * 16 + (cmd_ddic_oem_info[39] - 48);//x high byte
		oem_data[6] = (cmd_ddic_oem_info[40] - 48 ) * 16 + (cmd_ddic_oem_info[41] - 48);//y low byte
		oem_data[7] = (cmd_ddic_oem_info[42] - 48 ) * 16 + (cmd_ddic_oem_info[43] - 48);//y high byte
	}

	hostprocessing_set_bright_colorpoint_of_white(oem_data, hisifd);

	LCDKIT_INFO("finished\n");
}

static void hostprocessing_set_colorpoint_of_white(char *oem_data, struct hisi_fb_data_type *hisifd)
{
	//ddic set color point data 4bytes, the data format is :0x03,0x01,cxl,cxh,cyl,cyh
	char __iomem *mipi_dsi0_base = NULL;

	if ((NULL == hisifd) || (NULL == oem_data)) {
		LCDKIT_ERR("NULL pointer\n");
		return;
	}

	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	lcd_colorpoint_of_white[0] = oem_data[2];
	lcd_colorpoint_of_white[1] = oem_data[3];
	lcd_colorpoint_of_white[2] = oem_data[4];
	lcd_colorpoint_of_white[3] = oem_data[5];
	if (lcd_write_flag == 1) {
		oem_data[2] = lcd_brightness[0];
		oem_data[3] = lcd_brightness[1];
	} else {
		oem_data[2] = (cmd_ddic_oem_info[32] - 48 ) * 16 + (cmd_ddic_oem_info[33] - 48);//brightness low byte
		oem_data[3] = (cmd_ddic_oem_info[34] - 48 ) * 16 + (cmd_ddic_oem_info[35] - 48);//brightness high byte
	}
	oem_data[4] = lcd_colorpoint_of_white[0];
	oem_data[5] = lcd_colorpoint_of_white[1];
	oem_data[6] = lcd_colorpoint_of_white[2];
	oem_data[7] = lcd_colorpoint_of_white[3];

	hostprocessing_set_bright_colorpoint_of_white(oem_data, hisifd);

	LCDKIT_INFO("finished\n");
}

static void hostprocessing_set_rework(char *oem_data, struct hisi_fb_data_type *hisifd)
{
	if ((NULL == hisifd) || (NULL == oem_data)) {
		LCDKIT_ERR("NULL pointer\n");
		return;
	}

	LCDKIT_INFO("finished\n");
}

static struct ddic_oem_cmd read_cmds[] = {
	{HOST_OEM_PRODUCT_ID_TYPE, hostprocessing_get_ddic_product_id},
	{HOST_OEM_2D_BARCODE_TYPE, hostprocessing_get_2d_barcode},
	{HOST_OEM_BRIGHTNESS_TYPE, hostprocessing_get_brightness},
	{HOST_OEM_COLOROFWHITE_TYPE, hostprocessing_get_colorpoint_of_white},
	{HOST_OEM_BRIGHTNESSANDCOLOR_TYPE, hostprocessing_get_bright_colorpoint_of_white},
	{HOST_OEM_REWORK_TYPE, hostprocessing_get_rework},
};

static struct ddic_oem_cmd write_cmds[] = {
	{HOST_OEM_BRIGHTNESS_TYPE, hostprocessing_set_brightness},
	{HOST_OEM_COLOROFWHITE_TYPE, hostprocessing_set_colorpoint_of_white},
	{HOST_OEM_BRIGHTNESSANDCOLOR_TYPE, hostprocessing_set_bright_colorpoint_of_white},
	{HOST_OEM_REWORK_TYPE, hostprocessing_set_rework},
};

ssize_t host_panel_oem_info_show(void* pdata, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	int i = 0;
	char oemdataout[100] = {0};
	char str_oem[DDIC_OEM_INFO_SIZE_MAX] = {0};
	char str_tmp[DDIC_OEM_INFO_SIZE_MAX] = {0};

	if ((NULL == pdata) || (NULL == buf)) {
		LCDKIT_ERR("NULL pointer\n");
		return -EINVAL;
	}

	hisifd = (struct hisi_fb_data_type*) pdata;

	for (i = 0; i < sizeof(read_cmds)/sizeof(read_cmds[0]); i++) {
		if (ddic_oem_type == read_cmds[i].type) {
			LCDKIT_INFO("cmd = %d\n",ddic_oem_type);
		   (*read_cmds[i].func)(oemdataout, hisifd);
		}
	}

	memset(str_oem, 0, sizeof(str_oem));
	for(i = 0; i < oemdataout[1]; ++i) {
		memset(str_tmp, 0, sizeof(str_tmp));
		snprintf(str_tmp, sizeof(str_tmp), "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,",
		oemdataout[0+i*LCD_OEM_BLOCK_LEN],oemdataout[1+i*LCD_OEM_BLOCK_LEN],oemdataout[2+i*LCD_OEM_BLOCK_LEN],oemdataout[3+i*LCD_OEM_BLOCK_LEN],
		oemdataout[4+i*LCD_OEM_BLOCK_LEN],oemdataout[5+i*LCD_OEM_BLOCK_LEN],oemdataout[6+i*LCD_OEM_BLOCK_LEN],oemdataout[7+i*LCD_OEM_BLOCK_LEN],
		oemdataout[8+i*LCD_OEM_BLOCK_LEN],oemdataout[9+i*LCD_OEM_BLOCK_LEN],oemdataout[10+i*LCD_OEM_BLOCK_LEN],oemdataout[11+i*LCD_OEM_BLOCK_LEN],
		oemdataout[12+i*LCD_OEM_BLOCK_LEN],oemdataout[13+i*LCD_OEM_BLOCK_LEN],oemdataout[14+i*LCD_OEM_BLOCK_LEN],oemdataout[15+i*LCD_OEM_BLOCK_LEN]);
		strncat(str_oem, str_tmp,strlen(str_tmp));
	}

	ret = snprintf(buf, DDIC_OEM_INFO_SIZE_MAX, "%s\n", str_oem);

	return ret;
}

ssize_t host_panel_oem_info_store(void* pdata, char *buf)
{
	char *cur;
	char *token;
	char ddic_oem_info[DDIC_OEM_INFO_SIZE_MAX] = {0};
	char ddic_oem_check_info[DDIC_OEM_INFO_SIZE_MAX] = {0};
	int i = 0;
	int error = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	if ((NULL == pdata) || (NULL == buf)) {
		LCDKIT_ERR("NULL pointer\n");
		error = -EINVAL;
		goto out;
	}

	hisifd = (struct hisi_fb_data_type*) pdata;

	if (strlen(buf) < DDIC_OEM_INFO_SIZE_MAX) {
		cur = (char*)buf;
		token = strsep(&cur, ",");
		while (token) {
			ddic_oem_info[i++] = (unsigned char)simple_strtol(token, NULL, 0);
			token = strsep(&cur, ",");
		}
	} else {
		memcpy(ddic_oem_info, "INVALID", strlen("INVALID") + 1);
		LCDKIT_INFO("invalid cmd\n");
	}
	LCDKIT_INFO("%s: write Type=0x%2x , type data len=%d\n", __func__, ddic_oem_info[0], ddic_oem_info[1]);
	if (ddic_oem_info[0] < 0x0 || ddic_oem_info[0] > HOST_OEM_CHIP_TYPE_RESERVED) {
		LCDKIT_ERR("%s write Type=0x%2x is RESERVED\n", __func__, ddic_oem_info[0]);
		error = -EINVAL;
		goto out;
	}

	if ( ddic_oem_info[1] > HOST_OEM_CHIP_TYPE_LEN_RESERVED ) {
		LCDKIT_ERR("TPIC write RESERVED NV STRUCT len\n");
		error = -EINVAL;
		goto out;
	}

	ddic_oem_type = ddic_oem_info[0];

	//if the data length is 0, then just store the type
	if (ddic_oem_info[1] == 0x0) {
		LCDKIT_INFO("Just store type:%2x and then finished\n",ddic_oem_info[0]);
		return error;
	}

	//write tha oem_info to ddic
	for (i = 0; i < sizeof(write_cmds)/sizeof(write_cmds[0]); i++) {
		if (ddic_oem_type == write_cmds[i].type) {
		   (*write_cmds[i].func)(ddic_oem_info, hisifd);
		}
	}

	//check the write data
	for (i = 0; i < sizeof(read_cmds)/sizeof(read_cmds[0]); i++) {
		if (ddic_oem_type == read_cmds[i].type) {
		   (*read_cmds[i].func)(ddic_oem_check_info, hisifd);
		}
	}

	error = strncmp(ddic_oem_info, ddic_oem_check_info, ddic_oem_info[1] * 16);
	if( error ) {
		HISI_FB_INFO("Write type data has some error\n");
	}

out:
	LCDKIT_INFO("End\n");

	return error;
}


/*for lcd btb check*/
#include "lcdkit_btb_check.h"
#define BIT1_0	(0x3)
#define BIT31_2	(0xFFFFFFFC)
#define DELAY_TIME	(1000)
#define DELAY_1MS (1)
#define ERROR (-1)
#define RET (0)
#define NORMAL (1)

int lcdkit_get_gpio_val(struct gpio_desc *cmds)
{
	int val = -1;
	struct gpio_desc *cm = NULL;

	cm = cmds;
	if ((cm == NULL) || (cm->label == NULL)) {
		LCDKIT_ERR("cm or cm->label is null!\n");
		return ERROR;
	}

	if (!gpio_is_valid(*(cm->gpio))) {
		LCDKIT_ERR("gpio invalid, dtype=%d, lable=%s, gpio=%d!\n",
			cm->dtype, cm->label, *(cm->gpio));
		return ERROR;
	}

	if (cm->dtype == DTYPE_GPIO_INPUT) {
		if (gpio_direction_input(*(cm->gpio)) != 0) {
			LCDKIT_ERR("failed to gpio_direction_input, lable=%s, gpio=%d!\n",
				cm->label, *(cm->gpio));
			return ERROR;
		}
		val = gpiod_get_value(gpio_to_desc(*(cm->gpio)));
	} else {
		LCDKIT_ERR("dtype=%x NOT supported\n", cm->dtype);
		return ERROR;
	}

	if (cm->wait) {
		if (cm->waittype == WAIT_TYPE_US) {
			udelay(cm->wait);
		} else if (cm->waittype == WAIT_TYPE_MS) {
			mdelay(cm->wait);
		} else {
			mdelay(DELAY_TIME);	/*delay 1000ms for default*/
		}
	}

	return val;
}

int lcdkit_gpio_cmds_tx(unsigned int btb_gpio, int gpio_optype)
{
	if (btb_gpio == 0) {
		return ERROR;
	}

	lcd_btb_gpio = btb_gpio;
	if (gpio_optype == BTB_GPIO_REQUEST) {
		return gpio_cmds_tx(&lcd_gpio_request_btb, 1);
	} else if (gpio_optype == BTB_GPIO_READ) {
		return lcdkit_get_gpio_val(&lcd_gpio_read_btb);
	} else if (gpio_optype == BTB_GPIO_FREE) {
		return gpio_cmds_tx(&lcd_gpio_free_btb, 1);
	} else {
		return ERROR;
	}
}

int lcdkit_gpio_pulldown(void * btb_vir_addr)
{
	uint32_t btb_pull_data = 0;

	if (btb_vir_addr == NULL) {
		return RET;
	}
	btb_pull_data = readl(btb_vir_addr);		/* config pull down and read */
	if((btb_pull_data & BIT1_0) != PULLDOWN) {	/* (btb_pull_data & 0x3) != PULLDOWN */
		btb_pull_data = (btb_pull_data & BIT31_2) | (PULLDOWN & BIT1_0);	/* (btb_pull_data & 0xFFFFFFFC) | (PULLDOWN & 0x3) */
		writel(btb_pull_data, btb_vir_addr);
		mdelay(DELAY_1MS);
	}
	return NORMAL;
}

int lcdkit_gpio_pullup(void * btb_vir_addr)
{
	uint32_t btb_pull_data = 0;

	if (btb_vir_addr == NULL) {
		return RET;
	}
	btb_pull_data = readl(btb_vir_addr);		/* config pull up and read */
	if((btb_pull_data & BIT1_0) != PULLUP) {
		btb_pull_data = (btb_pull_data & BIT31_2) | (PULLUP & BIT1_0);
		writel(btb_pull_data, btb_vir_addr);
		mdelay(DELAY_1MS);
	}
	return NORMAL;
}
//lint -restore
extern ssize_t blkit_set_normal_work_mode(void);
extern ssize_t blkit_set_enhance_work_mode(void);

ssize_t lcdkit_set_bl_normal_mode_reg(void* pdata)
{
    ssize_t error = -1;
    struct hisi_fb_data_type *hisifd;

    hisifd = (struct hisi_fb_data_type*) pdata;
    if (I2C_ONLY_MODE == hisifd->panel_info.bl_ic_ctrl_mode)
    {
        error = blkit_set_normal_work_mode();
        if (error)
        {
            LCDKIT_ERR("blkit_set_normal_work_mode return error: %d \n", error);
        }
    }
    else
    {
        LCDKIT_INFO("not support \n");
    }

    LCDKIT_INFO("End error %d \n", error);
    return error;
}

ssize_t lcdkit_set_bl_enhance_mode_reg(void* pdata)
{
    ssize_t error = -1;
    struct hisi_fb_data_type *hisifd;

    hisifd = (struct hisi_fb_data_type*) pdata;
    if (I2C_ONLY_MODE == hisifd->panel_info.bl_ic_ctrl_mode)
    {
        error = blkit_set_enhance_work_mode();
        if (error)
        {
            LCDKIT_ERR("blkit_set_normal_work_mode return error: %d \n", error);
        }
    }
    else
    {
        LCDKIT_INFO("not support \n");
    }

    LCDKIT_INFO("End error %d \n", error);
    return error;
}
