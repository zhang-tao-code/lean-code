#include "pms.h"
#include "math.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct {
    char *cmd;
    ret_t (*proc)(char *result, uint32_t len);
} cmd_entry_t;

typedef enum{
		PMS_CMD_OK,
    PMS_RGNGE_ERROR,
    PMS_INVALID_ERROR
} error_t;

static ret_t cmd_psa(char *result, uint32_t len)
{
  pms_cmd_t *pms_ps=pms_get(); 
	if (!result || !len)
        return RET_ERR;

	snprintf(result, len, "%s%d", "+PS1=",pms_ps->psvalue[PMS_PS_CH1].PS);
  return RET_OK;
}

static ret_t cmd_psb(char *result, uint32_t len)
{
		pms_cmd_t *pms_ps=pms_get(); 
    if (!result || !len)
        return RET_ERR;

    snprintf(result, len,"%s%d", "+PS2=", pms_ps->psvalue[PMS_PS_CH2].PS);
    return RET_OK;
}
static ret_t cmd_psc(char *result, uint32_t len)
{
		pms_cmd_t *pms_ps=pms_get(); 
    if (!result || !len)
        return RET_ERR;

    snprintf(result, len, "%s%d", "+PS3=", pms_ps->psvalue[PMS_PS_CH3].PS);
    return RET_OK;
}

static ret_t cmd_psd(char *result, uint32_t len)
{
		pms_cmd_t *pms_ps=pms_get();;
    if (!result || !len)
        return RET_ERR;

    snprintf(result, len, "%s%d", "+PS4=", pms_ps->psvalue[PMS_PS_CH4].PS);
    return RET_OK;
}

static ret_t cmd_pstempa(char *result, uint32_t len)
{
  pms_cmd_t *pms_ps=pms_get(); 
	if (!result || !len)
        return RET_ERR;

    snprintf(result, len, "%s%.1f", "+PSTEMP1=",pms_ps->psvalue[PMS_PS_CH1].PSTEMP);
    return RET_OK;
}

static ret_t cmd_pstempb(char *result, uint32_t len)
{
   pms_cmd_t *pms_ps=pms_get();
	if(!result || !len)
        return RET_ERR;
		snprintf(result, len, "%s%.1f", "+PSTEMP2=",pms_ps->psvalue[PMS_PS_CH2].PSTEMP);
    return RET_OK;
}

static ret_t cmd_pstempc(char *result, uint32_t len)
{
		pms_cmd_t *pms_ps=pms_get(); 
    if (!result || !len)
        return RET_ERR;

    snprintf(result, len, "%s%.1f", "+PSTEMP3=", pms_ps->psvalue[PMS_PS_CH3].PSTEMP);
    return RET_OK;
}


static ret_t cmd_pstempd(char *result, uint32_t len)
{
		pms_cmd_t *pms_ps=pms_get(); 
    if (!result || !len)
        return RET_ERR;

    snprintf(result, len, "%s%.1f", "+PSTEMP4=", pms_ps->psvalue[PMS_PS_CH4].PSTEMP);
    return RET_OK;
}

static ret_t cmd_tempa(char *result, uint32_t len)
{
    pms_cmd_t *pms_temp=pms_get(); 
	 if (!result || !len)
	 {
			snprintf(result, len, "%d", PMS_INVALID_ERROR);
			return RET_ERR;
	 }
		if(pms_temp->tempvalue[PMS_TEMP_CH1].TEMP>100||pms_temp->tempvalue[PMS_TEMP_CH1].TEMP<0)
			snprintf(result, len, "%s%s%d", "+TEMP1=","E",PMS_RGNGE_ERROR);
		else
			snprintf(result, len, "%s%.1f", "+TEMP1=",pms_temp->tempvalue[PMS_TEMP_CH1].TEMP);
		return RET_OK;
}

static ret_t cmd_tempb(char *result, uint32_t len)
{
    pms_cmd_t *pms_temp=pms_get(); 
	 if (!result || !len)
	 {
			snprintf(result, len, "%d", PMS_INVALID_ERROR);
			return RET_ERR;
	 }
		if(pms_temp->tempvalue[PMS_TEMP_CH2].TEMP>100||pms_temp->tempvalue[PMS_TEMP_CH2].TEMP<0)
			snprintf(result, len, "%s%s%d", "+TEMP2=","E",PMS_RGNGE_ERROR);
		else
			snprintf(result, len, "%s%.1f", "+TEMP2=",pms_temp->tempvalue[PMS_TEMP_CH2].TEMP);
		return RET_OK;
}

static ret_t cmd_vol(char *result, uint32_t len)
{
  pms_cmd_t *pms_fbs=pms_get(); 
	if (!result || !len)
        return RET_ERR;

   snprintf(result, len, "%s%.1f", "+VOL=", pms_fbs->fbsvalue[ PMS_FBS_CH1].VOL);
   return RET_OK;
}
static ret_t cmd_flow(char *result, uint32_t len)
{
	 pms_cmd_t *pms_fbs=pms_get(); 
   if (!result || !len)
        return RET_ERR;

   snprintf(result, len, "%s%.1f", "+FLOW=", pms_fbs->fbsvalue[ PMS_FBS_CH1].FLOW);
   return RET_OK;
}

static ret_t cmd_bub(char *result, uint32_t len)
{
	 pms_cmd_t *pms_fbs=pms_get(); 
   if (!result || !len)
        return RET_ERR;

   snprintf(result, len, "%s%.1f", "+BUB=", pms_fbs->fbsvalue[ PMS_FBS_CH1].BUB);
   return RET_OK;
}

static ret_t cmd_bubtime(char *result, uint32_t len)
{
	 pms_cmd_t *pms_fbs=pms_get(); 
   if (!result || !len)
        return RET_ERR;
		
   snprintf(result, len, "%s%d", "+BUBTIME=", pms_fbs->fbsvalue[ PMS_FBS_CH1].BUBTIME);
   return RET_OK;
}

ret_t cmd_pack(char *result, uint32_t len)
{
  pms_cmd_t *pms_pack=pms_get();  
	if (!result || !len)
        return RET_ERR;
		
		snprintf(result, len, "%s%d", 	"+PS1=",pms_pack->psvalue[PMS_PS_CH1].PS);
		snprintf(result, len,	"%s%s%d", result,"+PS2=",pms_pack->psvalue[PMS_PS_CH2].PS);
		snprintf(result, len, "%s%s%d", result,"+PS3=",pms_pack->psvalue[PMS_PS_CH3].PS);
		snprintf(result, len, "%s%s%d", result,"+PS4=",pms_pack->psvalue[PMS_PS_CH4].PS);
	
		snprintf(result, len, "%s%s%.1f",result, "+PSTEMP1=",pms_pack->psvalue[PMS_PS_CH1].PSTEMP);
		snprintf(result, len, "%s%s%.1f",result, "+PSTEMP2=",pms_pack->psvalue[PMS_PS_CH2].PSTEMP);
		snprintf(result, len, "%s%s%.1f",result, "+PSTEMP3=",pms_pack->psvalue[PMS_PS_CH3].PSTEMP);
		snprintf(result, len, "%s%s%.1f",result, "+PSTEMP4=",pms_pack->psvalue[PMS_PS_CH4].PSTEMP);
	
		snprintf(result, len, "%s%s%.1f",result, "+TEMP1=",pms_pack->tempvalue[PMS_TEMP_CH1].TEMP);
		snprintf(result, len, "%s%s%.1f",result, "+TEMP2=",pms_pack->tempvalue[PMS_TEMP_CH2].TEMP);
		snprintf(result, len, "%s%s%.1f",result, "+VOL=", pms_pack->fbsvalue[ PMS_FBS_CH1].VOL);
		snprintf(result, len, "%s%s%.1f",result, "+FLOW=", pms_pack->fbsvalue[ PMS_FBS_CH1].FLOW);
		snprintf(result, len, "%s%s%.1f",result, "+BUB=", pms_pack->fbsvalue[ PMS_FBS_CH1].BUB);
		snprintf(result, len, "%s%s%d",	result, "+BUBTIME=", pms_pack->fbsvalue[ PMS_FBS_CH1].BUBTIME);
	
    return RET_OK;
}

static cmd_entry_t cmd_list[] = {
    { "AT+PS1",    		cmd_psa },
    { "AT+PS2",    		cmd_psb },
    { "AT+PS3",    		cmd_psc },
    { "AT+PS4",    		cmd_psd },
    { "AT+PSTEMP1",   cmd_pstempa },
    { "AT+PSTEMP2",   cmd_pstempb },
		{ "AT+PSTEMP3",   cmd_pstempc },
    { "AT+PSTEMP4",   cmd_pstempd },
    { "AT+TEMP1",    	cmd_tempa },
    { "AT+TEMP2",    	cmd_tempb },
    { "AT+VOL",   		cmd_vol },

    { "AT+FLOW",   		cmd_flow},
    { "AT+BUB",    		cmd_bub },
    { "AT+BUBTIME",   cmd_bubtime },
		{ "AT+PACK",   		cmd_pack },
    { NULL, NULL }
		
};


char *cmdnum,*cmdlen,*cmdcrc;uint16_t crcvalue;
void cmd_proc(char *cmd, char *rsp, uint16_t len)
{
    cmd_entry_t *entry;
    char result[256] = "";
		char delims[] = ",";
		char *psave;	
		//char *cmdnum,*cmdlen,*cmdcrc;
    ret_t ret = RET_ERR;

    if (!cmd || !strlen(cmd) || !rsp || !len)
			  return;   

    if (strncmp(cmd, "AT+", 3))
        goto done;
	
		cmdnum = strtok_r(cmd, delims ,&psave);		
		cmdlen = strtok_r(NULL, delims,&psave);
		cmdcrc = strtok_r(NULL, delims,&psave );	
		
//		crcvalue=crc16bitbybit((uint8_t *)cmdnum, strlen(cmdlen));//1F30		
//		if(crc16bitbybit((uint8_t *)cmdnum, strlen(cmdlen))==cmdcrc)
//		{	
//		
			for (entry = cmd_list; entry->cmd; entry++) {
        if (strncmp(entry->cmd, cmdnum , strlen(entry->cmd)))
            continue;
        ret = entry->proc(result, sizeof(result));
        break;
			}
			
//		}else{			
//			ret=RET_ERR;
//			//result="2";			
//		}
			crcvalue=crc16((uint8_t *)result, sizeof(result));			
			snprintf(result, len, "%s%s%d%s%d", result,",",strlen(result),",",crcvalue);
				
			
done:

    if (ret == RET_OK) {
            snprintf(rsp, len, "%s\r\n",result);
    } else {   
            snprintf(rsp, len, "+ERR=%s\r\n", result);

    }
}
