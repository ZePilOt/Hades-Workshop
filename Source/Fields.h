#ifndef _FIELDS_H
#define _FIELDS_H

// Many thanks to yaz0r and Zidane_2 for sharing scripts about reading field backgrounds
struct FieldTilesAnimDataStruct;
struct FieldTilesTileDataStruct;
struct FieldTilesUnkblockDataStruct;
struct FieldTilesCameraDataStruct;
struct FieldTilesDataStruct;

struct FieldWalkmeshDataStruct;

struct FieldRoleDataStruct;

struct FieldDataSet;

#include <inttypes.h>
#include <fstream>
#include "File_Manipulation.h"
#include "Configuration.h"
using namespace std;

struct FieldTilesAnimDataStruct {
public:
	uint8_t unk1;
	uint8_t tile_amount;
	uint16_t unk2;
	uint32_t unk3;
	uint32_t unk4;
	uint32_t tile_list_offset;
	uint8_t* tile_list;
	uint8_t* tile_duration;
};

struct FieldTilesTileDataStruct {
public:
	int16_t pos_x;
	int16_t pos_y;
	uint32_t unk1;
	uint32_t unk2;
	uint16_t unk3;
	uint16_t unk4;
	uint16_t camera_id;
	uint16_t tile_amount;
	uint32_t tile_pos_offset;
	uint32_t tile_data_offset;
	uint32_t tile_packet_offset;
	uint32_t unk5;
	uint8_t* tile_pos_unk1;
	uint8_t* tile_pos_unk2;
	uint8_t* tile_pos_x;
	uint8_t* tile_pos_y;
	
	bool is_static;
	uint32_t distance;
	uint16_t* tile_clut_y;
	uint8_t* tile_clut_x;
	uint8_t* tile_page_y;
	uint8_t* tile_page_x;
	uint8_t* tile_tp;
	uint8_t* tile_abr;
	uint8_t* tile_source_v;
	uint8_t* tile_source_u;
	bool* tile_packet_type;
	unsigned int* tile_steam_id;
	
	bool is_first_of_anim;
	uint8_t id;
	FieldTilesDataStruct* parent;
	
private:
	uint32_t data1;
	uint32_t data2;
	uint32_t data3;
	uint32_t data4;
	uint32_t data5;
	uint32_t* tile_data_data1;
	uint32_t* tile_data_data2;
	
	void AllocTileData();
	friend FieldTilesDataStruct;
};

struct FieldTilesUnkblockDataStruct {
public:
	
};

struct FieldTilesCameraDataStruct {
public:
	uint16_t size_ratio_y;
	uint16_t size_ratio_x;
	uint16_t angle_a; // walk no diff
	int16_t eye_x; // walk diff
	uint16_t angle_b; // walk no diff X
	int16_t eye_y; // walk no diff
	int16_t eye_z; // walk no diff X
	int16_t focal_x; // walk diff?
	int16_t focal_z; // walk no diff
	int16_t focal_y; // walk no diff Y
	int32_t offset_x;
	int32_t offset_z;
	int32_t offset_y;
	int16_t offset_x2;
	int16_t offset_y2;
	int16_t offset_x3;
	int16_t offset_y3;
	int16_t min_x;
	int16_t max_x;
	int16_t min_y;
	int16_t max_y;
	int16_t closeness;
	int16_t unk;
	
	int pos_x;
	int pos_y;
	unsigned int width;
	unsigned int height;
	
	void UpdateSize();
	unsigned int GetWidth();
	unsigned int GetHeight();
	
	uint8_t id;
	FieldTilesDataStruct* parent;
};

struct FieldTilesDataStruct : public ChunkChild {
public:
	// header
	uint16_t tiles_size;
	uint16_t unknown1;
	uint16_t anim_amount;
	uint16_t tiles_amount;
	uint16_t unkblock_amount;
	uint16_t camera_amount;
	uint32_t anim_offset;
	uint32_t tiles_offset;
	uint32_t unkblock_offset;
	uint32_t camera_offset;
	uint16_t anim_unk1;
	uint16_t tiles_unk1;
	uint16_t unkblock_unk1;
	uint16_t camera_unk1;
	uint16_t anim_unk2;
	uint16_t tiles_unk2;
	uint16_t unkblock_unk2;
	uint16_t camera_unk2;
	uint16_t anim_unk3;
	uint16_t tiles_unk3;
	uint16_t unkblock_unk3;
	uint16_t camera_unk3;
	FieldTilesAnimDataStruct* anim;
	FieldTilesTileDataStruct* tiles;
	FieldTilesUnkblockDataStruct* unkblock; // seems unused at all...
	FieldTilesCameraDataStruct* camera;
	
	FieldTilesTileDataStruct** tiles_sorted;
	
	~FieldTilesDataStruct();
	void Copy(FieldTilesDataStruct& cpy);
	uint32_t* ConvertAsImage(unsigned int cameraid, bool tileflag[] = NULL, bool showtp = false); // delete[] it
	int Export(const char* outputfile, unsigned int cameraid, bool tileflag[] = NULL, bool showtp = false, bool mergetiles = false);
	
	void Read(fstream& f);
	void Write(fstream& f);
	void WritePPF(fstream& f);
	void ReadHWS(fstream& f);
	void WriteHWS(fstream& f);
	
	unsigned int id;
	FieldDataSet* parent;
	
private:
	void ConvertDatas(bool readway);
	void AddTilesetToImage(uint32_t* imgdest, FieldTilesTileDataStruct& t, bool showtp = false, uint32_t* steamimg = NULL, uint32_t steamimgwidth = 1);
};

struct FieldWalkmeshDataStruct : public ChunkChild {
public:
	uint32_t magic_walkmesh;
	int16_t unknown1;
	int16_t offset_x2;
	int16_t offset_z2;
	int16_t offset_y2;
	int16_t offset_x;
	int16_t offset_z;
	int16_t offset_y;
	int16_t offset_x3;
	int16_t offset_z3;
	int16_t offset_y3;
	int16_t unknown4;
	int16_t unknown5;
	int16_t unknown6;
	int16_t unknown7;
	int16_t unknown8;
	int16_t unknown9;
	uint32_t unknown10;
	
	uint16_t triangle_amount;
	uint16_t triangle_offset;
	uint16_t indexunk_amount;
	uint16_t indexunk_offset;
	uint16_t unknown1_amount;
	uint16_t unknown1_offset;
	uint16_t walkpath_amount;
	uint16_t walkpath_offset;
	uint16_t unknown2_amount; // maybe link between walkpaths
	uint16_t unknown2_offset;
	uint16_t vertice_amount;
	uint16_t vertice_offset;
	
	uint8_t* triangle_unk1;
	uint8_t* triangle_stepsound;
	uint16_t* triangle_unk2;
	uint16_t* triangle_walkpath;
	uint16_t* triangle_unknown2;
	uint16_t* triangle_unk4;
	uint16_t* triangle_unk5;
	uint16_t* triangle_vertice1;
	uint16_t* triangle_vertice2;
	uint16_t* triangle_vertice3;
	uint16_t* triangle_indexunk1;
	uint16_t* triangle_indexunk2;
	uint16_t* triangle_indexunk3;
	uint16_t* triangle_adjacenttriangle1;
	uint16_t* triangle_adjacenttriangle2;
	uint16_t* triangle_adjacenttriangle3;
	int16_t* triangle_centerx;
	int16_t* triangle_centerz;
	int16_t* triangle_centery;
	uint16_t* triangle_unk9;
	uint16_t* triangle_unk10;
	
	uint16_t* indexunk_unk1;
	uint16_t* indexunk_unk2;
	
	uint16_t* unknown1_unk1;
	uint16_t* unknown1_unk2;
	uint16_t* unknown1_unk3;
	uint16_t* unknown1_unk4;
	uint32_t* unknown1_unk5;
	uint16_t* unknown1_unk6;
	uint16_t* unknown1_unk7;
	
	uint16_t* walkpath_unk1;
	uint16_t* walkpath_unk2;
	int16_t* walkpath_minx;
	int16_t* walkpath_minz;
	int16_t* walkpath_miny;
	int16_t* walkpath_offsetx;
	int16_t* walkpath_offsetz;
	int16_t* walkpath_offsety;
	int16_t* walkpath_unkx3;
	int16_t* walkpath_unkz3;
	int16_t* walkpath_unky3;
	int16_t* walkpath_unkx4;
	int16_t* walkpath_unkz4;
	int16_t* walkpath_unky4;
	uint16_t* walkpath_triangleamount;
	uint16_t* walkpath_trianglelistoffset;
	uint32_t** walkpath_trianglelist;
	
	uint32_t* unknown2_unk1;
	int16_t* unknown2_unka1;
	int16_t* unknown2_unkb1;
	int16_t* unknown2_unka2;
	int16_t* unknown2_unkb2;
	int16_t* unknown2_unka3;
	int16_t* unknown2_unkb3;
	
	int16_t* vertice_x;
	int16_t* vertice_z;
	int16_t* vertice_y;
	
	void Read(fstream& f);
	void Write(fstream& f);
	void WritePPF(fstream& f);
	void ReadHWS(fstream& f);
	void WriteHWS(fstream& f);
};

struct FieldRoleDataStruct : public ChunkChild {
public:
	uint32_t magic_role;
	uint16_t zero1;
	uint8_t unk1_amount;
	uint8_t unk1_amount2;
	uint8_t unk2_amount;
	uint8_t unk2_amount2;
	uint16_t zero2;
	
	uint8_t* unk1_unknown1;
	uint8_t* unk1_unknown2;
	uint8_t* unk1_unknown3;
	uint8_t* unk1_unknown4;
	uint8_t* unk1_unknown5;
	uint8_t* unk1_unknown6;
	uint8_t* unk1_unknown7;
	uint8_t* unk1_unknown8;
	uint8_t* unk1_unknown9;
	uint8_t* unk1_unknown10;
	uint8_t* unk1_unknown11;
	uint8_t* unk1_unknown12;
	
	uint16_t* unk2_model;
	uint8_t* unk2_unknown1;
	uint8_t* unk2_unknown2;
	uint8_t* unk2_unknown3;
	uint8_t* unk2_unknown4;
	uint8_t* unk2_unknown5;
	uint8_t* unk2_unknown6;
	
	int AddModelRole(uint16_t modelid);
	void RemoveModelRole(uint16_t unk2id);
	
	void Read(fstream& f);
	void Write(fstream& f);
	void WritePPF(fstream& f);
	void ReadHWS(fstream& f);
	void WriteHWS(fstream& f);
};

struct FieldDataSet {
public:
	uint16_t amount;
	uint16_t* cluster_id;
	uint16_t* struct_id;
	ScriptDataStruct** script_data;
	ImageMapDataStruct** preload;
	FieldTilesDataStruct** background_data;
	FieldWalkmeshDataStruct** walkmesh;
	TIMImageDataStruct** tim_data;
	FieldRoleDataStruct** role;
	
	TextDataStruct** related_text;
	uint32_t name_space_used; // Steam version only
	
	int SetFieldName(unsigned int fieldid, wstring newvalue);
	int SetFieldName(unsigned int fieldid, FF9String& newvalue);
	
	void Load(fstream& ffbin, ClusterSet& clusset, TextDataSet* textset = NULL);
	void Write(fstream& ffbin, ClusterSet& clusset);
	void WritePPF(fstream& ffbin, ClusterSet& clusset);
	// return value is int[5] to be deleted
	// {Number of oversized blocks, Number of unknown data, Number of unused blocks, Number of oversized parent block, Number of ignored Preload data}
	// Parent block is a data block containing preloading datas and TIM images in Field & World Map clusters.
	int* LoadHWS(fstream& ffhws, UnusedSaveBackupPart& backup, bool usetext, unsigned int localflag);
	void WriteHWS(fstream& ffhws, UnusedSaveBackupPart& backup, unsigned int localflag);
	void WriteSteamText(fstream& ffbin);
};

#endif