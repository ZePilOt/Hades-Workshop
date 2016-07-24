#include "File_IOCommon.h"

uint64_t ReadLongLong(fstream& f) {
	uint64_t res = (uint64_t)ReadLong(f);
	res |= ((uint64_t)ReadLong(f) << 32);
	return res;
}

uint32_t ReadLong(fstream& f) {
	uint32_t res = f.get();
	res |= f.get() << 8;
	res |= f.get() << 16;
	res |= f.get() << 24;
	return res;
}

uint32_t ReadLongBE(fstream& f) {
	uint32_t res = f.get() << 24;
	res |= f.get() << 16;
	res |= f.get() << 8;
	res |= f.get();
	return res;
}

uint32_t ReadLong3(fstream& f) {
	uint32_t res = f.get();
	res |= f.get() << 8;
	res |= f.get() << 16;
	return res;
}

uint16_t ReadShort(fstream& f) {
	uint32_t res = f.get();
	res |= f.get() << 8;
	return res;
}

uint16_t ReadShortBE(fstream& f) {
	uint32_t res = f.get() << 8;
	res |= f.get();
	return res;
}

void WriteLongLong(fstream& f, uint64_t value) {
	f.put(value & 0xFF);
	f.put((value >> 8) & 0xFF);
	f.put((value >> 16) & 0xFF);
	f.put((value >> 24) & 0xFF);
	f.put((value >> 32) & 0xFF);
	f.put((value >> 40) & 0xFF);
	f.put((value >> 48) & 0xFF);
	f.put((value >> 56) & 0xFF);
}

void WriteLong(fstream& f, uint32_t value) {
	f.put(value & 0xFF);
	f.put((value >> 8) & 0xFF);
	f.put((value >> 16) & 0xFF);
	f.put((value >> 24) & 0xFF);
}

void WriteLongBE(fstream& f, uint32_t value) {
	f.put((value >> 24) & 0xFF);
	f.put((value >> 16) & 0xFF);
	f.put((value >> 8) & 0xFF);
	f.put(value & 0xFF);
}

void WriteLong3(fstream& f, uint32_t value) {
	f.put(value & 0xFF);
	f.put((value >> 8) & 0xFF);
	f.put((value >> 16) & 0xFF);
}

void WriteShort(fstream& f, uint16_t value) {
	f.put(value & 0xFF);
	f.put((value >> 8) & 0xFF);
}

void WriteShortBE(fstream& f, uint16_t value) {
	f.put((value >> 8) & 0xFF);
	f.put(value & 0xFF);
}

uint32_t GetAlignOffset(uint32_t baseoffset, uint32_t align) {
	align--;
	return (((baseoffset+align) & ~align)-baseoffset);
}

uint32_t iobuffer_offset;
void BufferInitPosition(uint32_t pos) {
	iobuffer_offset = pos;
}

uint32_t BufferGetPosition() {
	return iobuffer_offset;
}

uint64_t BufferReadLongLong(uint8_t* buffer, uint64_t& destvalue) {
	uint32_t part;
	destvalue = (uint64_t)BufferReadLong(buffer,part);
	destvalue |= ((uint64_t)BufferReadLong(buffer,part) << 32);
	return destvalue;
}

uint32_t BufferReadLong(uint8_t* buffer, uint32_t& destvalue) {
	destvalue = buffer[iobuffer_offset++];
	destvalue |= buffer[iobuffer_offset++] << 8;
	destvalue |= buffer[iobuffer_offset++] << 16;
	destvalue |= buffer[iobuffer_offset++] << 24;
	return destvalue;
}

uint32_t BufferReadLongBE(uint8_t* buffer, uint32_t& destvalue) {
	destvalue = buffer[iobuffer_offset++] << 24;
	destvalue |= buffer[iobuffer_offset++] << 16;
	destvalue |= buffer[iobuffer_offset++] << 8;
	destvalue |= buffer[iobuffer_offset++];
	return destvalue;
}

uint32_t BufferReadLong3(uint8_t* buffer, uint32_t& destvalue) {
	destvalue = buffer[iobuffer_offset++];
	destvalue |= buffer[iobuffer_offset++] << 8;
	destvalue |= buffer[iobuffer_offset++] << 16;
	return destvalue;
}

uint16_t BufferReadShort(uint8_t* buffer, uint16_t& destvalue) {
	destvalue = buffer[iobuffer_offset++];
	destvalue |= buffer[iobuffer_offset++] << 8;
	return destvalue;
}

uint16_t BufferReadShortBE(uint8_t* buffer, uint16_t& destvalue) {
	destvalue = buffer[iobuffer_offset++] << 8;
	destvalue |= buffer[iobuffer_offset++];
	return destvalue;
}

uint8_t BufferReadChar(uint8_t* buffer, uint8_t& destvalue) {
	destvalue = buffer[iobuffer_offset++];
	return destvalue;
}

void BufferWriteLongLong(uint8_t* buffer, uint64_t value) {
	buffer[iobuffer_offset++] = (value & 0xFF);
	buffer[iobuffer_offset++] = ((value >> 8) & 0xFF);
	buffer[iobuffer_offset++] = ((value >> 16) & 0xFF);
	buffer[iobuffer_offset++] = ((value >> 24) & 0xFF);
	buffer[iobuffer_offset++] = ((value >> 32) & 0xFF);
	buffer[iobuffer_offset++] = ((value >> 40) & 0xFF);
	buffer[iobuffer_offset++] = ((value >> 48) & 0xFF);
	buffer[iobuffer_offset++] = ((value >> 56) & 0xFF);
}

void BufferWriteLong(uint8_t* buffer, uint32_t value) {
	buffer[iobuffer_offset++] = (value & 0xFF);
	buffer[iobuffer_offset++] = ((value >> 8) & 0xFF);
	buffer[iobuffer_offset++] = ((value >> 16) & 0xFF);
	buffer[iobuffer_offset++] = ((value >> 24) & 0xFF);
}

void BufferWriteLongBE(uint8_t* buffer, uint32_t value) {
	buffer[iobuffer_offset++] = ((value >> 24) & 0xFF);
	buffer[iobuffer_offset++] = ((value >> 16) & 0xFF);
	buffer[iobuffer_offset++] = ((value >> 8) & 0xFF);
	buffer[iobuffer_offset++] = (value & 0xFF);
}

void BufferWriteLong3(uint8_t* buffer, uint32_t value) {
	buffer[iobuffer_offset++] = (value & 0xFF);
	buffer[iobuffer_offset++] = ((value >> 8) & 0xFF);
	buffer[iobuffer_offset++] = ((value >> 16) & 0xFF);
}

void BufferWriteShort(uint8_t* buffer, uint16_t value) {
	buffer[iobuffer_offset++] = (value & 0xFF);
	buffer[iobuffer_offset++] = ((value >> 8) & 0xFF);
}

void BufferWriteShortBE(uint8_t* buffer, uint16_t value) {
	buffer[iobuffer_offset++] = ((value >> 8) & 0xFF);
	buffer[iobuffer_offset++] = (value & 0xFF);
}

void BufferWriteChar(uint8_t* buffer, uint8_t value) {
	buffer[iobuffer_offset++] = value;
}
