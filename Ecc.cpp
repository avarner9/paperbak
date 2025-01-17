////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// Reed-Solomon (255,223) encoding/decoding                                   //
// Derived from the software by Phil Karn                                     //
// Copyright 2002 Phil Karn, KA9Q                                             //
// May be used under the terms of the GNU General Public License (GPL)        //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <string.h>

typedef unsigned char  uchar;
typedef unsigned int   uint;

uchar alpha[] = {
  0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,
  0x87, 0x89, 0x95, 0xad, 0xdd, 0x3d, 0x7a, 0xf4,
  0x6f, 0xde, 0x3b, 0x76, 0xec, 0x5f, 0xbe, 0xfb,
  0x71, 0xe2, 0x43, 0x86, 0x8b, 0x91, 0xa5, 0xcd,
  0x1d, 0x3a, 0x74, 0xe8, 0x57, 0xae, 0xdb, 0x31,
  0x62, 0xc4, 0x0f, 0x1e, 0x3c, 0x78, 0xf0, 0x67,
  0xce, 0x1b, 0x36, 0x6c, 0xd8, 0x37, 0x6e, 0xdc,
  0x3f, 0x7e, 0xfc, 0x7f, 0xfe, 0x7b, 0xf6, 0x6b,
  0xd6, 0x2b, 0x56, 0xac, 0xdf, 0x39, 0x72, 0xe4,
  0x4f, 0x9e, 0xbb, 0xf1, 0x65, 0xca, 0x13, 0x26,
  0x4c, 0x98, 0xb7, 0xe9, 0x55, 0xaa, 0xd3, 0x21,
  0x42, 0x84, 0x8f, 0x99, 0xb5, 0xed, 0x5d, 0xba,
  0xf3, 0x61, 0xc2, 0x03, 0x06, 0x0c, 0x18, 0x30,
  0x60, 0xc0, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0,
  0x47, 0x8e, 0x9b, 0xb1, 0xe5, 0x4d, 0x9a, 0xb3,
  0xe1, 0x45, 0x8a, 0x93, 0xa1, 0xc5, 0x0d, 0x1a,
  0x34, 0x68, 0xd0, 0x27, 0x4e, 0x9c, 0xbf, 0xf9,
  0x75, 0xea, 0x53, 0xa6, 0xcb, 0x11, 0x22, 0x44,
  0x88, 0x97, 0xa9, 0xd5, 0x2d, 0x5a, 0xb4, 0xef,
  0x59, 0xb2, 0xe3, 0x41, 0x82, 0x83, 0x81, 0x85,
  0x8d, 0x9d, 0xbd, 0xfd, 0x7d, 0xfa, 0x73, 0xe6,
  0x4b, 0x96, 0xab, 0xd1, 0x25, 0x4a, 0x94, 0xaf,
  0xd9, 0x35, 0x6a, 0xd4, 0x2f, 0x5e, 0xbc, 0xff,
  0x79, 0xf2, 0x63, 0xc6, 0x0b, 0x16, 0x2c, 0x58,
  0xb0, 0xe7, 0x49, 0x92, 0xa3, 0xc1, 0x05, 0x0a,
  0x14, 0x28, 0x50, 0xa0, 0xc7, 0x09, 0x12, 0x24,
  0x48, 0x90, 0xa7, 0xc9, 0x15, 0x2a, 0x54, 0xa8,
  0xd7, 0x29, 0x52, 0xa4, 0xcf, 0x19, 0x32, 0x64,
  0xc8, 0x17, 0x2e, 0x5c, 0xb8, 0xf7, 0x69, 0xd2,
  0x23, 0x46, 0x8c, 0x9f, 0xb9, 0xf5, 0x6d, 0xda,
  0x33, 0x66, 0xcc, 0x1f, 0x3e, 0x7c, 0xf8, 0x77,
  0xee, 0x5b, 0xb6, 0xeb, 0x51, 0xa2, 0xc3, 0x00
};

uchar ecc_index[] = {
   255,    0,    1,   99,    2,  198,  100,  106,
     3,  205,  199,  188,  101,  126,  107,   42,
     4,  141,  206,   78,  200,  212,  189,  225,
   102,  221,  127,   49,  108,   32,   43,  243,
     5,   87,  142,  232,  207,  172,   79,  131,
   201,  217,  213,   65,  190,  148,  226,  180,
   103,   39,  222,  240,  128,  177,   50,   53,
   109,   69,   33,   18,   44,   13,  244,   56,
     6,  155,   88,   26,  143,  121,  233,  112,
   208,  194,  173,  168,   80,  117,  132,   72,
   202,  252,  218,  138,  214,   84,   66,   36,
   191,  152,  149,  249,  227,   94,  181,   21,
   104,   97,   40,  186,  223,   76,  241,   47,
   129,  230,  178,   63,   51,  238,   54,   16,
   110,   24,   70,  166,   34,  136,   19,  247,
    45,  184,   14,   61,  245,  164,   57,   59,
     7,  158,  156,  157,   89,  159,   27,    8,
   144,    9,  122,   28,  234,  160,  113,   90,
   209,   29,  195,  123,  174,   10,  169,  145,
    81,   91,  118,  114,  133,  161,   73,  235,
   203,  124,  253,  196,  219,   30,  139,  210,
   215,  146,   85,  170,   67,   11,   37,  175,
   192,  115,  153,  119,  150,   92,  250,   82,
   228,  236,   95,   74,  182,  162,   22,  134,
   105,  197,   98,  254,   41,  125,  187,  204,
   224,  211,   77,  140,  242,   31,   48,  220,
   130,  171,  231,   86,  179,  147,   64,  216,
    52,  176,  239,   38,   55,   12,   17,   68,
   111,  120,   25,  154,   71,  116,  167,  193,
    35,   83,  137,  251,   20,   93,  248,  151,
    46,   75,  185,   96,   15,  237,   62,  229,
   246,  135,  165,   23,   58,  163,   60,  183
};

uchar poly[] = {
     0,  249,   59,   66,    4,   43,  126,  251,
    97,   30,    3,  213,   50,   66,  170,    5,
    24,    5,  170,   66,   50,  213,    3,   30,
    97,  251,  126,   43,    4,   66,   59,  249,
     0
};

void Encode8(uchar *data,uchar *bb,int pad) {
  int i,j;
  uchar feedback;
  memset(bb,0,32);
  for (i=0; i<223-pad; i++) {
    feedback=ecc_index[data[i]^bb[0]];
    if (feedback!=255) {
      for (j=1; j<32; j++) {
	bb[j]^=alpha[(feedback+poly[32-j])%255];
      };
    };
    memmove(bb,bb+1,31);
    if (feedback!=255)
      bb[31]=alpha[(feedback+poly[0])%255];
    else
      bb[31]=0;
    ;
  };
};

int Decode8(uchar *data,int *eras_pos,int no_eras,int pad) {
  int i,j,r,k,deg_lambda,el,deg_omega;
  int syn_error,count;
  uchar u,q,tmp,num1,num2,den,discr_r;
  uchar lambda[33],s[32],b[33],t[33],omega[33];
  uchar root[32],reg[33],loc[32];
  for (i=0; i<32; i++)
    s[i]=data[0];
  for (j=1; j<255-pad; j++) {
    for (i=0; i<32; i++) {
      if (s[i]==0)
	s[i]=data[j];
      else
	s[i]=data[j]^alpha[(ecc_index[s[i]]+(112+i)*11)%255];
      ;
    };
  };
  syn_error=0;
  for (i=0; i<32; i++) {
    syn_error|=s[i];
    s[i]=ecc_index[s[i]]; };
  if (syn_error==0) {
    count=0; goto finish; };
  memset(lambda+1,0,32);
  lambda[0]=1;
  if (no_eras>0) {
    lambda[1]=alpha[(11*(254-eras_pos[0]))%255];
    for (i=1; i<no_eras; i++) {
      u=(uchar)((11*(254-eras_pos[i]))%255);
      for (j=i+1; j>0; j--) {
	tmp=ecc_index[lambda[j-1]];
	if (tmp!=255) lambda[j]^=alpha[(u+tmp)%255];
      };
    };
  };
  for (i=0; i<33; i++)
    b[i]=ecc_index[lambda[i]];
  r=el=no_eras;
  while (++r<=32) {
    discr_r=0;
    for (i=0; i<r; i++) {
      if ((lambda[i]!=0) && (s[r-i-1]!=255)) {
	discr_r^=alpha[(ecc_index[lambda[i]]+s[r-i-1])%255];
      };
    };
    discr_r=ecc_index[discr_r];
    if (discr_r==255) {
      memmove(b+1,b,32);
      b[0]=255; }
    else {
      t[0]=lambda[0];
      for (i=0; i<32; i++) {
	if (b[i]!=255)
	  t[i+1]=lambda[i+1]^alpha[(discr_r+b[i])%255];
	else
	  t[i+1]=lambda[i+1];
        ;
      };
      if (2*el<=r+no_eras-1) {
	el=r+no_eras-el;
	for (i=0; i<=32; i++)
	  b[i]=(uchar)(lambda[i]==0?255:(ecc_index[lambda[i]]-discr_r+255)%255);
        ; }
      else {
	memmove(b+1,b,32);
	b[0]=255; };
      memcpy(lambda,t,33);
    };
  };
  deg_lambda=0;
  for (i=0; i<33; i++) {
    lambda[i]=ecc_index[lambda[i]];
    if (lambda[i]!=255) deg_lambda=i; };
  memcpy(reg+1,lambda+1,32);
  count=0;
  for (i=1,k=115; i<=255; i++,k=(k+116)%255) {
    q=1;
    for (j=deg_lambda; j>0; j--) {
      if (reg[j]!=255) {
	reg[j]=(uchar)((reg[j]+j)%255);
	q^=alpha[reg[j]];
      };
    };
    if (q!=0) continue;
    root[count]=(uchar)i;
    loc[count]=(uchar)k;
    if (++count==deg_lambda) break;
  };
  if (deg_lambda!=count) {
    count=-1;
    goto finish; };
  deg_omega=deg_lambda-1;
  for (i=0; i<=deg_omega; i++ ) {
    tmp=0;
    for (j=i; j>=0; j--) {
      if ((s[i-j]!=255) && (lambda[j]!=255)) {
	tmp^=alpha[(s[i-j]+lambda[j])%255];
      };
    };
    omega[i]=ecc_index[tmp];
  };
  for (j=count-1; j>=0; j--) {
    num1=0;
    for (i=deg_omega; i>=0; i--) {
      if (omega[i]!=255) {
	num1^=alpha[(omega[i]+i*root[j])%255];
      };
    };
    num2=alpha[(root[j]*111+255)%255];
    den=0;
    for (i=(deg_lambda<31?deg_lambda:31) & ~1; i>=0; i-=2) {
      if (lambda[i+1]!=255) {
	den^=alpha[(lambda[i+1]+i*root[j])%255];
      };
    };
    if (num1!=0 && loc[j]>=pad) {
      data[loc[j]-pad]^=alpha[(ecc_index[num1]+ecc_index[num2]+255-ecc_index[den])%255];
    };
  };
finish:
  if (eras_pos!=NULL) {
    for (i=0; i<count; i++) eras_pos[i]=loc[i]; };
  return count;
};

