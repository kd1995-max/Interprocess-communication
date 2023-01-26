extern char *calculate_file_md5(const char *filename);
extern void backup_after_every_5_second();
extern void create_backup();
extern int is_MD5_digest_same();
extern void create_structure_array();
extern void find_the_fields();
extern void find_the_fields(size_t n_access_backup_points,size_t n_access_orignal_points,struct backup_data *bd, struct orignal_data *od);
extern void read_the_changes();
extern void A();
