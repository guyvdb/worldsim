#include <catch2.hpp>
#include <string>
//#include <iostream>
#include <utils.h>

//#include <utils.h>
//#include <store.h>
#include <cache/cache.h>
//#include <file.h>

struct CacheInfoTest {
    graph::type::gid Id;
    graph::cache::CacheOffset Info;
};

/*

id	foff	fend	pstart	pend	poff
1	0	6	0	0	0
2	7	13	0	0	7
3	14	20	0	0	14
4	21	27	0	0	21
5	28	34	0	1	28
6	35	41	1	1	3
7	42	48	1	1	10
8	49	55	1	1	17
9	56	62	1	1	24
10	63	69	1	2	31
11	70	76	2	2	6
12	77	83	2	2	13
13	84	90	2	2	20
14	91	97	2	3	27
15	98	104	3	3	2
16	105	111	3	3	9
17	112	118	3	3	16
18	119	125	3	3	23
19	126	132	3	4	30
20	133	139	4	4	5
21	140	146	4	4	12
22	147	153	4	4	19
23	154	160	4	5	26
24	161	167	5	5	1
25	168	174	5	5	8
26	175	181	5	5	15
27	182	188	5	5	22
28	189	195	5	6	29
29	196	202	6	6	4
30	203	209	6	6	11
31	210	216	6	6	18
32	217	223	6	6	25
33	224	230	7	7	0
34	231	237	7	7	7


  */

TEST_CASE("Should calculate offsets","[graph][cache]") {
/*
  std::size_t recordsize = 7;
  std::size_t pagesize = 32;


  graph::Cache *c = new graph::Cache(0x0,graph::Storeable::Concept::Test,recordsize, pagesize);

  //id	foff	fend	pstart	pend	poff
  // 7	 42	   48	    1	      1	   10
  CacheInfoTest data[] = {
    {7,{42, 48, 1, 1, 10 } },
    {10,{	63,	69,	1,	2,	31}}
  };


  for(auto &d : data) {
    graph::CacheObjectInfo i = c->ObjectInfo(d.Id);
    REQUIRE(i.FileOffset == d.Info.FileOffset);
    REQUIRE(i.FileEndset == d.Info.FileEndset);
    REQUIRE(i.PageStart == d.Info.PageStart);
    REQUIRE(i.PageEnd == d.Info.PageEnd);
    REQUIRE(i.PageOffset == d.Info.PageOffset);
    REQUIRE(i.Len == recordsize);
  }


  delete c;
  */
}
