#ifdef _MSC_VER
#pragma pack(push)
#pragma pack(1)
#define PACKED
#else
#define PACKED __attribute__((packed))
#endif
