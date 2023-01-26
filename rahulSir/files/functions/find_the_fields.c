#include "/home/krishanudev/rahulSir/files/headers/headers.h"

/*
*   Function description
*   This function will find the field differences
*
*/
void find_the_fields(size_t n_access_backup_points,size_t n_access_orignal_points,struct backup_data *bd, struct orignal_data *od)
{
    FILE *fp;

   fp = fopen("changes.txt", "w+");
                
    char tmp[1024];
    
    //find changes in snr and channel
    for(size_t i = 0; i < n_access_backup_points; i++){
        for(size_t j = 0; j < n_access_orignal_points; j++){ 
           
           char *ssid_b = (bd + i)-> SSID;
           char *snr_b = (bd + i)-> snr;
           char *channel_b = (bd + i)-> channel;
           
           char *ssid_o = (od + j)-> SSID;
           char *snr_o = (od + i)-> snr;
           char *channel_o = (od + i)-> channel;
                     
           if(!strcmp(ssid_b,ssid_o)){
            
            if(strcmp(snr_b,snr_o))
            {
                //printf("\n%s's SNR has changed from %s to %s\n", ssid_b , snr_b, snr_o);
                fprintf(fp,"\n%s's SNR has changed from %s to %s\n", ssid_b , snr_b, snr_o);
            }
            
            if(strcmp(channel_b,channel_o))
            {
                //printf("\n%s's channel has changed from %s to %s\n", ssid_b , channel_b, channel_o);
                fprintf(fp,"\n%s's channel has changed from %s to %s\n", ssid_b , channel_b, channel_o);  
            }
           }
        }
    }
    
    // find the removed SSID
    for(size_t i = 0; i < n_access_backup_points; i++){
        int flag = 0;
        char *ssid_b = (bd + i)-> SSID;
        for(size_t j = 0; j < n_access_orignal_points; j++){
            char *ssid_o = (od + j)-> SSID;
            
            if(!strcmp(ssid_b,ssid_o))
                flag = 1;
        }
        if(flag == 0)
        fprintf(fp,"\n%s is removed from the list\n",ssid_b);        
    }
    
    //find the added ssid
    for(size_t i = 0; i < n_access_orignal_points; i++){
        int flag = 0;
        char *ssid_o = (od + i)-> SSID;
        char *snr_o = (od + i)-> snr;
        char *channel_o = (od + i)-> channel;
        
        for(size_t j = 0; j < n_access_backup_points; j++){
            char *ssid_b = (bd + j)-> SSID;
            
            if(!strcmp(ssid_o,ssid_b))
                flag = 1;
        }
        if(flag == 0)
        fprintf(fp,"\n%s is added to the list with SNR %s and channel %s\n",ssid_o,snr_o,channel_o);       
    }
    fclose(fp);
}
