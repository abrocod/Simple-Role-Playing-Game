#include "display2.h"

using namespace std;

Display::Display() {
	char temp [] = {
'|','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','|',
'|','|','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','|',' ',' ',' ',' ','|','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','|',' ',' ',' ',' ','|','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','|','|',
'|','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|','|',
'|','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|','|',
'|','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|','|',
'|','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|','|',
'|','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','+','#','#','#','#','+','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','+','#','#','#','#','+','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|','|',
'|','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|','|',
'|','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|','|',
'|','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|','|',
'|','|','-','-','-','-','-','-','-','-','-','+','-','-','-','-','-','-','-','-','-','-','-','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','-','-','-','-','-','-','-','-','-','-','-','-','+','-','-','-','-','-','-','-','-','|','|',
'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
'|','|','-','-','-','-','-','-','-','-','-','+','-','-','-','-','-','-','-','-','-','-','-','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','-','-','-','-','-','-','-','-','-','-','-','-','+','-','-','-','-','-','-','-','-','|','|',
'|','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|','|',
'|','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|','|',
'|','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|','|',
'|','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|','|',
'|','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','+','#','#','#','#','+','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','+','#','#','#','#','+','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|','|',
'|','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|','|',
'|','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|','|',
'|','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',' ',' ',' ',' ','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|','|',
'|','|','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','|',' ',' ',' ',' ','|','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','|',' ',' ',' ',' ','|','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','|','|',
'|','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','|',
};
	display_vec.assign(temp, temp+VEC_LENGTH); // convert array into vector
	

	
	// define 5 arrays, and then convert them into vector:
	int chamber1[] = { 160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,318,319,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,397,398,399,400,401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416,417,476,477,478,479,480,481,482,483,484,485,486,487,488,489,490,491,492,493,494,495,496,555,556,557,558,559,560,561,562,563,564,565,566,567,568,569,570,571,572,573,574,575,634,635,636,637,638,639,640,641,642,643,644,645,646,647,648,649,650,651,652,653,654,713,714,715,716,717,718,719,720,721,722,723,724,725,726,727,728,729,730,731,732,733};
	int chamber2[] = { 187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,360,361,362,363,364,365,424,425,426,427,428,429,430,431,432,433,434,435,436,437,438,439,440,441,442,443,444,503,504,505,506,507,508,509,510,511,512,513,514,515,516,517,518,519,520,521,522,523,582,583,584,585,586,587,588,589,590,591,592,593,594,595,596,597,598,599,600,601,602,661,662,663,664,665,666,667,668,669,670,671,672,673,674,675,676,677,678,679,680,681,740,741,742,743,744,745,746,747,748,749,750,751,752,753,754,755,756,757,758,759,760,819,820,821,822,823,824,825,826,827,828,829,830,831,832,833,834,835,836,837,838,839,898,899,900,901,902,903,904,905,906,907,908,909,910,911,912,913,914,915,916,917,918,977,978,979,980,981,982,983,984,985,986,987,988,989,990,991,992,993,994,995,996,997,1056,1057,1058,1059,1060,1061,1062,1063,1064,1065,1066,1067,1068,1069,1070,1071,1072,1073,1074,1075,1076,1135,1136,1137,1138,1139,1140,1141,1142,1143,1144,1145,1146,1147,1148,1149,1150,1151,1152,1153,1154,1155,1214,1215,1216,1217,1218,1219,1220,1221,1222,1223,1224,1225,1226,1227,1228,1229,1230,1231,1232,1233,1234,1293,1294,1295,1296,1297,1298,1299,1300,1301,1302,1303,1304,1305,1306,1307,1308,1309,1310,1311,1312,1313,1372,1373,1374,1375,1376,1377,1378,1379,1380,1381,1382,1383,1384,1385,1386,1387,1388,1389,1390,1391,1392,1451,1452,1453,1454,1455,1456,1457,1458,1459,1460,1461,1462,1463,1464,1465,1466,1467,1468,1469,1470,1471,1530,1531,1532,1533,1534,1535,1536,1537,1538,1539,1540,1541,1542,1543,1544,1545,1546,1547,1548,1549,1550,1609,1610,1611,1612,1613,1614,1615,1616,1617,1618,1619,1620,1621,1622,1623,1624,1625,1626,1627,1628,1629,1688,1689,1690,1691,1692,1693,1694,1695,1696,1697,1698,1699,1700,1701,1702,1703,1704,1705,1706,1707,1708,1767,1768,1769,1770,1771,1772,1773,1774,1775,1776,1777,1778,1779,1780,1781,1782,1783,1784,1785,1786,1787};
	int chamber3[] ={ 214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,372,373,374,375,376,377,378,379,380,381,382,383,384,385,386,387,388,389,390,391,392,451,452,453,454,455,456,457,458,459,460,461,462,463,464,465,466,467,468,469,470,471,530,531,532,533,534,535,536,537,538,539,540,541,542,543,544,545,546,547,548,549,550,609,610,611,612,613,614,615,616,617,618,619,620,621,622,623,624,625,626,627,628,629,688,689,690,691,692,693,694,695,696,697,698,699,700,701,702,703,704,705,706,707,708,767,768,769,770,771,772,773,774,775,776,777,778,779,780,781,782,783,784,785,786,787};
	int chamber4[] ={ 1187,1188,1189,1190,1191,1192,1193,1194,1195,1196,1197,1198,1199,1200,1201,1202,1203,1204,1205,1206,1207,1266,1267,1268,1269,1270,1271,1272,1273,1274,1275,1276,1277,1278,1279,1280,1281,1282,1283,1284,1285,1286,1345,1346,1347,1348,1349,1350,1351,1352,1353,1354,1355,1356,1357,1358,1359,1360,1361,1362,1363,1364,1365,1424,1425,1426,1427,1428,1429,1430,1431,1432,1433,1434,1435,1436,1437,1438,1439,1440,1441,1442,1443,1444,1503,1504,1505,1506,1507,1508,1509,1510,1511,1512,1513,1514,1515,1516,1517,1518,1519,1520,1521,1522,1523,1582,1583,1584,1585,1586,1587,1588,1589,1590,1591,1592,1593,1594,1595,1596,1597,1598,1599,1600,1601,1602,1661,1662,1663,1664,1665,1666,1667,1668,1669,1670,1671,1672,1673,1674,1675,1676,1677,1678,1679,1680,1681,1740,1741,1742,1743,1744,1745,1746,1747,1748,1749,1750,1751,1752,1753,1754,1755,1756,1757,1758,1759,1760};
	int chamber5[] = { 1241,1242,1243,1244,1245,1246,1247,1248,1249,1250,1251,1252,1253,1254,1255,1256,1257,1258,1259,1260,1261,1320,1321,1322,1323,1324,1325,1326,1327,1328,1329,1330,1331,1332,1333,1334,1335,1336,1337,1338,1339,1340,1399,1400,1401,1402,1403,1404,1405,1406,1407,1408,1409,1410,1411,1412,1413,1414,1415,1416,1417,1418,1419,1478,1479,1480,1481,1482,1483,1484,1485,1486,1487,1488,1489,1490,1491,1492,1493,1494,1495,1496,1497,1498,1557,1558,1559,1560,1561,1562,1563,1564,1565,1566,1567,1568,1569,1570,1571,1572,1573,1574,1575,1576,1577,1636,1637,1638,1639,1640,1641,1642,1643,1644,1645,1646,1647,1648,1649,1650,1651,1652,1653,1654,1655,1656,1715,1716,1717,1718,1719,1720,1721,1722,1723,1724,1725,1726,1727,1728,1729,1730,1731,1732,1733,1734,1735,1794,1795,1796,1797,1798,1799,1800,1801,1802,1803,1804,1805,1806,1807,1808,1809,1810,1811,1812,1813,1814};
	
		
	//vector<int> display_chamber_array[5];
	length_ch1 = sizeof(chamber1)/sizeof(chamber1[0]);
	length_ch2 = sizeof(chamber2)/sizeof(chamber2[0]);
	length_ch3 = sizeof(chamber3)/sizeof(chamber3[0]);
	length_ch4 = sizeof(chamber4)/sizeof(chamber4[0]);
	length_ch5 = sizeof(chamber5)/sizeof(chamber5[0]);	
	
	chamber1_vec.assign(chamber1, chamber1+length_ch1);
	chamber2_vec.assign(chamber2, chamber2+length_ch2);
	chamber3_vec.assign(chamber3, chamber3+length_ch3);
	chamber4_vec.assign(chamber4, chamber4+length_ch4);
	chamber5_vec.assign(chamber5, chamber5+length_ch5);
	
	display_chamber_vec.push_back(chamber1_vec);
	display_chamber_vec.push_back(chamber2_vec);
	display_chamber_vec.push_back(chamber3_vec);
	display_chamber_vec.push_back(chamber4_vec);
	display_chamber_vec.push_back(chamber5_vec);

};


void Display::prettyprint() {
	// print display_vec to stdout as a nice game board
	int i = 0;
	for (int j=0; j<NUM_ROW; j++) {
		for (int k=0; k<NUM_COL; k++) {
			cout << display_vec.at(i);
			++i;
		}
		cout << endl;
	};
};

void Display::notified(int index, char symbol) {
	this->display_vec.at(index) = symbol;
} 








