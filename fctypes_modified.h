#ifndef FIRECAMJ_DATATYPES
#define FIRECAMJ_DATATYPES

//linux and macos X
#if defined(linux) || defined(LINUX) || defined(__linux) || defined(__linux__) || defined(macosx)

   #if defined(linux) || defined(LINUX) || defined(__linux) || defined(__linux__)
      #define FIREC_LINUX
   #else
      #define FIREC_MACOSX
   #endif

   #ifdef __BIG_ENDIAN__
      #define FIREC_BIG_ENDIAN
   #else
      #define FIREC_LITTLE_ENDIAN
   #endif

   #include <stdint.h>
   typedef int           fint;
   typedef unsigned int  fuint;
   typedef unsigned char fuchar;
   typedef signed char   fchar;
   typedef int8_t        fint8;
   typedef uint8_t       fuint8;
   typedef int16_t       fint16;
   typedef uint16_t      fuint16;
   typedef int32_t       fint32;
   typedef uint32_t      fuint32;
   typedef int64_t       fint64;
   typedef uint64_t      fuint64;

#endif

//windows
//#ifdef _MSC_VER
   #define FIREC_MSWIN
   #define FIREC_LITTLE_ENDIAN

    typedef int              fint;
   typedef unsigned int     fuint;
   typedef unsigned char    fuchar;
   typedef signed char      fchar;
   //typedef __int8           fint8;
   typedef char             fint8;

   //typedef unsigned __int8	fuint8;
   typedef unsigned char	fuint8;
   
   //typedef __int16  				fint16;
   typedef short  				fint16;
   
   //typedef unsigned __int16	fuint16;
   
   typedef unsigned short	fuint16;
   
   //typedef __int32  				fint32;
   typedef int  				fint32;
  
   //typedef unsigned __int32 fuint32;
   typedef unsigned int fuint32;
   
   typedef __int64  				fint64;
   typedef unsigned __int64 fuint64;

//#endif

//functions to convert integers from host to little endian byte order and vice versa
fuint8  htole8(fuint8 in);
fuint16 htole16(fuint16 in);
fuint32 htole32(fuint32 in);

fuint8 letoh8(fuint8 in);
fuint16 letoh16(fuint16 in);
fuint32 letoh32(fuint32 in);


#define htole8(in)  (in)
#define letoh8(in)  (in)
#ifdef FIREC_LITTLE_ENDIAN
   #define htole16(in)  (in)
   #define htole32(in)  (in)
   #define letoh16(in)  (in)
   #define letoh32(in)  (in)
#else

fuint16 htole16(fuint16 in)  {return (((in&0x00ff)<<8) | ((in&0xff00)>>8));}
fuint32 htole32(fuint32 in)  {return (((in&0x000000ff)<<24) | ((in&0x0000ff00)<<8) | ((in&0x00ff0000)>>8) | ((in&0xff000000)>>24));}

fuint16 letoh16(fuint16 in)  {return htole16(in);}
fuint32 letoh32(fuint32 in)  {return htole32(in);}

#endif

#endif // FIRECAMJ_DATATYPES
	
