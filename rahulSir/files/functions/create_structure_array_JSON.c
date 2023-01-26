#include "/home/krishanudev/rahulSir/files/headers/headers.h"

/*
 * Description of the below fuction
 * filling the structure defined in files/header/var/h
 */

void create_structure_array()
{
    //store the parsed data in buffer_backup 
    char buffer_backup[1024]; 
    char buffer_orignal[1024]; 
    
    //keep the JSON object and will use to fetch the properties 
    struct json_object *parsed_backup_json; 
    struct json_object *parsed_orignal_json;
    
    //store the size of access_points array 
    size_t n_access_backup_points; 
    size_t n_access_orignal_points; 
    
    //open the backup.json file in read only mode 
    FILE *fp_backup = fopen("files/backup/backup.json","r"); 
    fread(buffer_backup, 1024, 1 , fp_backup); 
    fclose(fp_backup); 
    
    //open the access_points.json file in read only mode 
    FILE *fp_orignal = fopen("/tmp/access_points.json","r"); 
    fread(buffer_orignal, 1024, 1 , fp_orignal); 
    fclose(fp_orignal); 
    
    //parssing the JSON file and storing it in buffer_backup 
    parsed_backup_json = json_tokener_parse(buffer_backup); 
    
    //parssing the JSON file and storing it in buffer_orignal 
    parsed_orignal_json = json_tokener_parse(buffer_orignal); 
    
    //with additional bytes in str to continue the parsing. 
    struct json_object *access_points_backup;
    json_object_object_get_ex(parsed_backup_json, "access_points", &access_points_backup);
    
    struct json_object *access_points_orignal;
    json_object_object_get_ex(parsed_orignal_json, "access_points", &access_points_orignal);

    //get the length of an array 
    n_access_backup_points = json_object_array_length(access_points_backup); 
    n_access_orignal_points = json_object_array_length(access_points_orignal); 
    
    struct backup_data *bd;
    // Memory allocation for backup_data structures
    bd = (struct backup_data *) malloc(n_access_backup_points * sizeof(struct backup_data));
    
    struct orignal_data *od;
    // Memory allocation for backup_data structures
    od = (struct orignal_data *) malloc(n_access_orignal_points * sizeof(struct orignal_data));
    
    //accessing the objects in an array of access_points_backup and storing it in ob structure array    
    for(size_t i=0;i<n_access_backup_points;i++){ 

        struct json_object *ob = json_object_array_get_idx(access_points_backup, i); 
 
        struct json_object *ssid; 
        json_object_object_get_ex(ob, "ssid", &ssid);
        
        struct json_object *snr; 
        json_object_object_get_ex(ob, "snr", &snr);
        
        struct json_object *channel;
        json_object_object_get_ex(ob, "channel", &channel);
        
        (bd + i)-> SSID = json_object_get_string(ssid);
        (bd + i)-> snr = json_object_get_string(snr);
        (bd + i)-> channel = json_object_get_string(channel);
            
    } 
    
    //accessing the objects in an array of access_points_backup and storing it in ob structure array    
    for(size_t i=0;i<n_access_orignal_points;i++){ 

        struct json_object *ob = json_object_array_get_idx(access_points_orignal, i); 
 
        struct json_object *ssid; 
        json_object_object_get_ex(ob, "ssid", &ssid);
        
        struct json_object *snr; 
        json_object_object_get_ex(ob, "snr", &snr);
        
        struct json_object *channel;
        json_object_object_get_ex(ob, "channel", &channel);
        
        (od + i)-> SSID = json_object_get_string(ssid);
        (od + i)-> snr = json_object_get_string(snr);
        (od + i)-> channel = json_object_get_string(channel);
            
    }
   
    find_the_fields(n_access_backup_points,n_access_orignal_points,bd,od);
}
