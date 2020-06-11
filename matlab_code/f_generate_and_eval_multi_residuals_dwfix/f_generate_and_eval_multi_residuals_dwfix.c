/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_generate_and_eval_multi_residuals_dwfix.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 11-Jun-2020 08:14:38
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "f_generate_and_eval_multi_residuals_dwfix_emxutil.h"
#include "sum.h"
#include "abs.h"
#include "mean.h"
#include "var.h"
#include "sort1.h"
#include "median.h"
#include "f_GLT.h"
#include "f_compute_detuning.h"
#include "f_computeQL.h"
#include "f_calibrateData.h"
#include "exp.h"
#include "f_generate_online_parityRes2_full.h"
#include "f_generate_online_parityRes1_full.h"
#include "f_generate_online_UKF_residual_full_dwfix.h"
#include "cov.h"
#include "f_generate_online_UKF_residual_full.h"

/* Function Declarations */
static double rt_roundd_snf(double u);

/* Function Definitions */

/*
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/*
 * This function evaluates the residual
 * Arguments    : const emxArray_real_T *PA
 *                emxArray_real_T *PP
 *                const emxArray_real_T *FA
 *                emxArray_real_T *FP
 *                const emxArray_real_T *RA
 *                emxArray_real_T *RP
 *                double FS
 *                double F0
 *                const creal_T cal_coeff[4]
 *                emxArray_real_T *dwfix
 *                const double tau_m[4]
 *                const double K_m[4]
 *                const double X0[4]
 *                double QL_nom
 *                double DELAY
 *                double FILLING
 *                double FLATTOP
 *                const double Sigma_nom_UKF[4]
 *                const double Sigma_nom_UKF_dwfix[4]
 *                const double r_mean_nom_UKF_dwfix[2]
 *                const double r_mean_nom_UKF[2]
 *                const double MeasNoiseVar[4]
 *                const double ProcessVar[36]
 *                double alpha
 *                double Sigma_nom_dw
 *                const emxArray_real_T *r_PS1_nom
 *                double Sigma_nom_PS1
 *                emxArray_real_T *s_max_UKF
 *                emxArray_real_T *s_max_UKF_dwfix
 *                emxArray_real_T *s_max_dw
 *                emxArray_real_T *s_max_PS1
 *                emxArray_real_T *res_PS2
 *                double *classis_UKF
 *                double *classis_dwfix
 *                double *classis_PS
 *                double *classis_dw
 *                double *strengthis_UKF
 *                double *strengthis_dwfix
 *                double *strengthis_PS
 *                double *strengthis_dw
 *                double *max_UKF
 *                double *max_dwfix
 *                double *max_PS
 *                double *max_dw
 *                double *median_UKF
 *                double *median_dwfix
 *                double *median_PS
 *                double *median_dw
 *                double *mode_UKF
 *                double *mode_dwfix
 *                double *mode_PS
 *                double *mode_dw
 *                double *var_UKF
 *                double *var_dwfix
 *                double *var_PS
 *                double *var_dw
 *                double *rm_I
 *                double *rm_Q
 *                double *rm_I_dwfix
 *                double *rm_Q_dwfix
 *                double *rvar_1
 *                double *rvar_2
 *                double *rvar_3
 *                double *QL
 *                double *dw_stat
 *                double *SP_F
 *                double *SP_P
 *                double *PC
 *                double *calib_check
 *                double *dec_hq
 *                double *zpth
 * Return Type  : void
 */
void f_generate_and_eval_multi_residuals_dwfix(const emxArray_real_T *PA,
  emxArray_real_T *PP, const emxArray_real_T *FA, emxArray_real_T *FP, const
  emxArray_real_T *RA, emxArray_real_T *RP, double FS, double F0, const creal_T
  cal_coeff[4], emxArray_real_T *dwfix, const double tau_m[4], const double K_m
  [4], const double X0[4], double QL_nom, double DELAY, double FILLING, double
  FLATTOP, const double Sigma_nom_UKF[4], const double Sigma_nom_UKF_dwfix[4],
  const double r_mean_nom_UKF_dwfix[2], const double r_mean_nom_UKF[2], const
  double MeasNoiseVar[4], const double ProcessVar[36], double alpha, double
  Sigma_nom_dw, const emxArray_real_T *r_PS1_nom, double Sigma_nom_PS1,
  emxArray_real_T *s_max_UKF, emxArray_real_T *s_max_UKF_dwfix, emxArray_real_T *
  s_max_dw, emxArray_real_T *s_max_PS1, emxArray_real_T *res_PS2, double
  *classis_UKF, double *classis_dwfix, double *classis_PS, double *classis_dw,
  double *strengthis_UKF, double *strengthis_dwfix, double *strengthis_PS,
  double *strengthis_dw, double *max_UKF, double *max_dwfix, double *max_PS,
  double *max_dw, double *median_UKF, double *median_dwfix, double *median_PS,
  double *median_dw, double *mode_UKF, double *mode_dwfix, double *mode_PS,
  double *mode_dw, double *var_UKF, double *var_dwfix, double *var_PS, double
  *var_dw, double *rm_I, double *rm_Q, double *rm_I_dwfix, double *rm_Q_dwfix,
  double *rvar_1, double *rvar_2, double *rvar_3, double *QL, double *dw_stat,
  double *SP_F, double *SP_P, double *PC, double *calib_check, double *dec_hq,
  double *zpth)
{
  double fs;
  emxArray_real_T *Rise;
  emxArray_real_T *Flattop;
  emxArray_real_T *Decay;
  double x;
  double mtmp;
  int i0;
  double ndbl;
  double apnd;
  double cdiff;
  double absa;
  double d;
  double absb;
  int k;
  int s;
  emxArray_real_T *idxP;
  emxArray_real_T *dw;
  int nm1d2;
  emxArray_boolean_T *b_x;
  emxArray_int32_T *ii;
  emxArray_boolean_T *b_RP;
  emxArray_boolean_T *b_PP;
  int exitg1;
  int i1;
  int idx;
  boolean_T guard1 = false;
  boolean_T b_FP[1361];
  static const short iv0[1361] = { 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70,
    71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
    90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106,
    107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121,
    122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136,
    137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151,
    152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166,
    167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181,
    182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196,
    197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211,
    212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226,
    227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241,
    242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256,
    257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271,
    272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286,
    287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301,
    302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316,
    317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331,
    332, 333, 334, 335, 336, 337, 338, 339, 340, 341, 342, 343, 344, 345, 346,
    347, 348, 349, 350, 351, 352, 353, 354, 355, 356, 357, 358, 359, 360, 361,
    362, 363, 364, 365, 366, 367, 368, 369, 370, 371, 372, 373, 374, 375, 376,
    377, 378, 379, 380, 381, 382, 383, 384, 385, 386, 387, 388, 389, 390, 391,
    392, 393, 394, 395, 396, 397, 398, 399, 400, 401, 402, 403, 404, 405, 406,
    407, 408, 409, 410, 411, 412, 413, 414, 415, 416, 417, 418, 419, 420, 421,
    422, 423, 424, 425, 426, 427, 428, 429, 430, 431, 432, 433, 434, 435, 436,
    437, 438, 439, 440, 441, 442, 443, 444, 445, 446, 447, 448, 449, 450, 451,
    452, 453, 454, 455, 456, 457, 458, 459, 460, 461, 462, 463, 464, 465, 466,
    467, 468, 469, 470, 471, 472, 473, 474, 475, 476, 477, 478, 479, 480, 481,
    482, 483, 484, 485, 486, 487, 488, 489, 490, 491, 492, 493, 494, 495, 496,
    497, 498, 499, 500, 501, 502, 503, 504, 505, 506, 507, 508, 509, 510, 511,
    512, 513, 514, 515, 516, 517, 518, 519, 520, 521, 522, 523, 524, 525, 526,
    527, 528, 529, 530, 531, 532, 533, 534, 535, 536, 537, 538, 539, 540, 541,
    542, 543, 544, 545, 546, 547, 548, 549, 550, 551, 552, 553, 554, 555, 556,
    557, 558, 559, 560, 561, 562, 563, 564, 565, 566, 567, 568, 569, 570, 571,
    572, 573, 574, 575, 576, 577, 578, 579, 580, 581, 582, 583, 584, 585, 586,
    587, 588, 589, 590, 591, 592, 593, 594, 595, 596, 597, 598, 599, 600, 601,
    602, 603, 604, 605, 606, 607, 608, 609, 610, 611, 612, 613, 614, 615, 616,
    617, 618, 619, 620, 621, 622, 623, 624, 625, 626, 627, 628, 629, 630, 631,
    632, 633, 634, 635, 636, 637, 638, 639, 640, 641, 642, 643, 644, 645, 646,
    647, 648, 649, 650, 651, 652, 653, 654, 655, 656, 657, 658, 659, 660, 661,
    662, 663, 664, 665, 666, 667, 668, 669, 670, 671, 672, 673, 674, 675, 676,
    677, 678, 679, 680, 681, 682, 683, 684, 685, 686, 687, 688, 689, 690, 691,
    692, 693, 694, 695, 696, 697, 698, 699, 700, 701, 702, 703, 704, 705, 706,
    707, 708, 709, 710, 711, 712, 713, 714, 715, 716, 717, 718, 719, 720, 721,
    722, 723, 724, 725, 726, 727, 728, 729, 730, 731, 732, 733, 734, 735, 736,
    737, 738, 739, 740, 741, 742, 743, 744, 745, 746, 747, 748, 749, 750, 751,
    752, 753, 754, 755, 756, 757, 758, 759, 760, 761, 762, 763, 764, 765, 766,
    767, 768, 769, 770, 771, 772, 773, 774, 775, 776, 777, 778, 779, 780, 781,
    782, 783, 784, 785, 786, 787, 788, 789, 790, 791, 792, 793, 794, 795, 796,
    797, 798, 799, 800, 801, 802, 803, 804, 805, 806, 807, 808, 809, 810, 811,
    812, 813, 814, 815, 816, 817, 818, 819, 820, 821, 822, 823, 824, 825, 826,
    827, 828, 829, 830, 831, 832, 833, 834, 835, 836, 837, 838, 839, 840, 841,
    842, 843, 844, 845, 846, 847, 848, 849, 850, 851, 852, 853, 854, 855, 856,
    857, 858, 859, 860, 861, 862, 863, 864, 865, 866, 867, 868, 869, 870, 871,
    872, 873, 874, 875, 876, 877, 878, 879, 880, 881, 882, 883, 884, 885, 886,
    887, 888, 889, 890, 891, 892, 893, 894, 895, 896, 897, 898, 899, 900, 901,
    902, 903, 904, 905, 906, 907, 908, 909, 910, 911, 912, 913, 914, 915, 916,
    917, 918, 919, 920, 921, 922, 923, 924, 925, 926, 927, 928, 929, 930, 931,
    932, 933, 934, 935, 936, 937, 938, 939, 940, 941, 942, 943, 944, 945, 946,
    947, 948, 949, 950, 951, 952, 953, 954, 955, 956, 957, 958, 959, 960, 961,
    962, 963, 964, 965, 966, 967, 968, 969, 970, 971, 972, 973, 974, 975, 976,
    977, 978, 979, 980, 981, 982, 983, 984, 985, 986, 987, 988, 989, 990, 991,
    992, 993, 994, 995, 996, 997, 998, 999, 1000, 1001, 1002, 1003, 1004, 1005,
    1006, 1007, 1008, 1009, 1010, 1011, 1012, 1013, 1014, 1015, 1016, 1017, 1018,
    1019, 1020, 1021, 1022, 1023, 1024, 1025, 1026, 1027, 1028, 1029, 1030, 1031,
    1032, 1033, 1034, 1035, 1036, 1037, 1038, 1039, 1040, 1041, 1042, 1043, 1044,
    1045, 1046, 1047, 1048, 1049, 1050, 1051, 1052, 1053, 1054, 1055, 1056, 1057,
    1058, 1059, 1060, 1061, 1062, 1063, 1064, 1065, 1066, 1067, 1068, 1069, 1070,
    1071, 1072, 1073, 1074, 1075, 1076, 1077, 1078, 1079, 1080, 1081, 1082, 1083,
    1084, 1085, 1086, 1087, 1088, 1089, 1090, 1091, 1092, 1093, 1094, 1095, 1096,
    1097, 1098, 1099, 1100, 1101, 1102, 1103, 1104, 1105, 1106, 1107, 1108, 1109,
    1110, 1111, 1112, 1113, 1114, 1115, 1116, 1117, 1118, 1119, 1120, 1121, 1122,
    1123, 1124, 1125, 1126, 1127, 1128, 1129, 1130, 1131, 1132, 1133, 1134, 1135,
    1136, 1137, 1138, 1139, 1140, 1141, 1142, 1143, 1144, 1145, 1146, 1147, 1148,
    1149, 1150, 1151, 1152, 1153, 1154, 1155, 1156, 1157, 1158, 1159, 1160, 1161,
    1162, 1163, 1164, 1165, 1166, 1167, 1168, 1169, 1170, 1171, 1172, 1173, 1174,
    1175, 1176, 1177, 1178, 1179, 1180, 1181, 1182, 1183, 1184, 1185, 1186, 1187,
    1188, 1189, 1190, 1191, 1192, 1193, 1194, 1195, 1196, 1197, 1198, 1199, 1200,
    1201, 1202, 1203, 1204, 1205, 1206, 1207, 1208, 1209, 1210, 1211, 1212, 1213,
    1214, 1215, 1216, 1217, 1218, 1219, 1220, 1221, 1222, 1223, 1224, 1225, 1226,
    1227, 1228, 1229, 1230, 1231, 1232, 1233, 1234, 1235, 1236, 1237, 1238, 1239,
    1240, 1241, 1242, 1243, 1244, 1245, 1246, 1247, 1248, 1249, 1250, 1251, 1252,
    1253, 1254, 1255, 1256, 1257, 1258, 1259, 1260, 1261, 1262, 1263, 1264, 1265,
    1266, 1267, 1268, 1269, 1270, 1271, 1272, 1273, 1274, 1275, 1276, 1277, 1278,
    1279, 1280, 1281, 1282, 1283, 1284, 1285, 1286, 1287, 1288, 1289, 1290, 1291,
    1292, 1293, 1294, 1295, 1296, 1297, 1298, 1299, 1300, 1301, 1302, 1303, 1304,
    1305, 1306, 1307, 1308, 1309, 1310, 1311, 1312, 1313, 1314, 1315, 1316, 1317,
    1318, 1319, 1320, 1321, 1322, 1323, 1324, 1325, 1326, 1327, 1328, 1329, 1330,
    1331, 1332, 1333, 1334, 1335, 1336, 1337, 1338, 1339, 1340, 1341, 1342, 1343,
    1344, 1345, 1346, 1347, 1348, 1349, 1350, 1351, 1352, 1353, 1354, 1355, 1356,
    1357, 1358, 1359, 1360, 1361, 1362, 1363, 1364, 1365, 1366, 1367, 1368, 1369,
    1370, 1371, 1372, 1373, 1374, 1375, 1376, 1377, 1378, 1379, 1380, 1381, 1382,
    1383, 1384, 1385, 1386, 1387, 1388, 1389, 1390, 1391, 1392, 1393, 1394, 1395,
    1396, 1397, 1398, 1399, 1400, 1401, 1402, 1403, 1404, 1405, 1406, 1407, 1408,
    1409, 1410, 1411, 1412, 1413, 1414, 1415, 1416, 1417, 1418, 1419, 1420 };

  emxArray_real_T *b_FA;
  emxArray_real_T *y;
  emxArray_creal_T *y_mC;
  emxArray_real_T *res_full_mean;
  emxArray_real_T *res_full_variance;
  emxArray_creal_T *u_mCal;
  emxArray_creal_T *r_mCal;
  boolean_T exitg2;
  emxArray_int32_T *r0;
  emxArray_real_T *r1;
  emxArray_boolean_T *c_FP;
  emxArray_creal_T *b_u_mCal;
  emxArray_creal_T *c_u_mCal;
  emxArray_real_T *b_PA;
  emxArray_real_T *b_dw;
  emxArray_real_T *b_s_max_dw;
  emxArray_real_T *c_s_max_dw;
  emxArray_real_T *d_s_max_dw;
  emxArray_boolean_T *e_s_max_dw;
  emxArray_real_T *c_dw;
  emxArray_creal_T *d_u_mCal;
  emxArray_creal_T *b_y_mC;
  emxArray_creal_T *c_FA;
  emxArray_creal_T *b_RA;
  emxArray_real_T *b_s_max_UKF_dwfix;
  emxArray_real_T *c_s_max_UKF_dwfix;
  emxArray_real_T *d_s_max_UKF_dwfix;
  emxArray_boolean_T *e_s_max_UKF_dwfix;
  emxArray_real_T *b_s_max_UKF;
  emxArray_real_T *c_s_max_UKF;
  emxArray_real_T *d_s_max_UKF;
  emxArray_boolean_T *e_s_max_UKF;
  emxArray_real_T *b_s_max_PS1;
  emxArray_real_T *c_s_max_PS1;
  emxArray_real_T *d_s_max_PS1;
  emxArray_boolean_T *e_s_max_PS1;
  emxArray_real_T *b_idxP;
  emxArray_real_T *b_res_full_mean;
  emxArray_real_T *c_res_full_mean;
  emxArray_real_T *d_res_full_mean;
  emxArray_real_T *e_res_full_mean;
  emxArray_real_T *f_res_full_mean;
  emxArray_real_T *c_PA;
  boolean_T b_guard1 = false;
  short ii_data[1361];
  short idxF_data[1361];
  double tmp_data[1361];
  double b_classis_UKF;
  double b_classis_PS;
  double b_classis_dwfix;
  double b_strengthis_UKF;
  double b_strengthis_PS;
  double b_strengthis_dw;
  double b_strengthis_dwfix;
  double b_mtmp;
  double c_mtmp;
  double d_mtmp;
  double e_mtmp;
  double b_median_UKF;
  double b_median_PS;
  double b_median_dw;
  double b_median_dwfix;
  double b_rm_I;
  double M;
  double b_M;
  double c_M;
  double d_M;
  double b_var_UKF;
  double b_var_dwfix;
  double b_var_PS;
  double b_rm_Q;
  double b_rm_I_dwfix;
  double b_rm_Q_dwfix;
  double b_rvar_1;
  double b_rvar_2;
  double b_rvar_3;
  double b_calib_check;
  double res_var_data[4];
  int res_var_size[2];
  fs = FS * 1.0E+6;
  emxInit_real_T(&Rise, 2);
  emxInit_real_T(&Flattop, 2);
  emxInit_real_T(&Decay, 2);
  if (fs == 1.0E+6) {
    x = rt_roundd_snf(DELAY * 1.0E+6 * 1.0E-6);
    mtmp = rt_roundd_snf(DELAY * 1.0E+6 * 1.0E-6 + FILLING * 1.0E+6 * 1.0E-6);
    if (rtIsNaN(x) || rtIsNaN(mtmp)) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Rise, i0, sizeof(double));
      Rise->data[0] = rtNaN;
    } else if (mtmp < x) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)Rise, i0, sizeof(double));
    } else if ((rtIsInf(x) || rtIsInf(mtmp)) && (x == mtmp)) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Rise, i0, sizeof(double));
      Rise->data[0] = rtNaN;
    } else if (x == x) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = (int)(mtmp - x) + 1;
      emxEnsureCapacity((emxArray__common *)Rise, i0, sizeof(double));
      k = (int)(mtmp - x);
      for (i0 = 0; i0 <= k; i0++) {
        Rise->data[Rise->size[0] * i0] = x + (double)i0;
      }
    } else {
      ndbl = floor((mtmp - x) + 0.5);
      apnd = x + ndbl;
      cdiff = apnd - mtmp;
      absa = fabs(x);
      absb = fabs(mtmp);
      if ((absa > absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = mtmp;
      } else if (cdiff > 0.0) {
        apnd = x + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        s = (int)ndbl;
      } else {
        s = 0;
      }

      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = s;
      emxEnsureCapacity((emxArray__common *)Rise, i0, sizeof(double));
      if (s > 0) {
        Rise->data[0] = x;
        if (s > 1) {
          Rise->data[s - 1] = apnd;
          nm1d2 = (s - 1) / 2;
          for (k = 1; k < nm1d2; k++) {
            Rise->data[k] = x + (double)k;
            Rise->data[(s - k) - 1] = apnd - (double)k;
          }

          if (nm1d2 << 1 == s - 1) {
            Rise->data[nm1d2] = (x + apnd) / 2.0;
          } else {
            Rise->data[nm1d2] = x + (double)nm1d2;
            Rise->data[nm1d2 + 1] = apnd - (double)nm1d2;
          }
        }
      }
    }

    d = (Rise->data[Rise->size[1] - 1] + 1.0) + rt_roundd_snf(FLATTOP * 1.0E+6 *
      1.0E-6);
    if (rtIsNaN(Rise->data[Rise->size[1] - 1] + 1.0) || rtIsNaN(d)) {
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Flattop, i0, sizeof(double));
      Flattop->data[0] = rtNaN;
    } else if (d < Rise->data[Rise->size[1] - 1] + 1.0) {
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)Flattop, i0, sizeof(double));
    } else if ((rtIsInf(Rise->data[Rise->size[1] - 1] + 1.0) || rtIsInf(d)) &&
               (Rise->data[Rise->size[1] - 1] + 1.0 == d)) {
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Flattop, i0, sizeof(double));
      Flattop->data[0] = rtNaN;
    } else if (floor(Rise->data[Rise->size[1] - 1] + 1.0) == Rise->data
               [Rise->size[1] - 1] + 1.0) {
      mtmp = Rise->data[Rise->size[1] - 1] + 1.0;
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = (int)floor(d - mtmp) + 1;
      emxEnsureCapacity((emxArray__common *)Flattop, i0, sizeof(double));
      k = (int)floor(d - mtmp);
      for (i0 = 0; i0 <= k; i0++) {
        Flattop->data[Flattop->size[0] * i0] = mtmp + (double)i0;
      }
    } else {
      ndbl = floor((d - (Rise->data[Rise->size[1] - 1] + 1.0)) + 0.5);
      apnd = (Rise->data[Rise->size[1] - 1] + 1.0) + ndbl;
      cdiff = apnd - d;
      absa = fabs(Rise->data[Rise->size[1] - 1] + 1.0);
      absb = fabs(d);
      if ((absa > absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = d;
      } else if (cdiff > 0.0) {
        apnd = (Rise->data[Rise->size[1] - 1] + 1.0) + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        s = (int)ndbl;
      } else {
        s = 0;
      }

      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = s;
      emxEnsureCapacity((emxArray__common *)Flattop, i0, sizeof(double));
      if (s > 0) {
        Flattop->data[0] = Rise->data[Rise->size[1] - 1] + 1.0;
        if (s > 1) {
          Flattop->data[s - 1] = apnd;
          nm1d2 = (s - 1) / 2;
          for (k = 1; k < nm1d2; k++) {
            Flattop->data[k] = (Rise->data[Rise->size[1] - 1] + 1.0) + (double)k;
            Flattop->data[(s - k) - 1] = apnd - (double)k;
          }

          if (nm1d2 << 1 == s - 1) {
            Flattop->data[nm1d2] = ((Rise->data[Rise->size[1] - 1] + 1.0) + apnd)
              / 2.0;
          } else {
            Flattop->data[nm1d2] = (Rise->data[Rise->size[1] - 1] + 1.0) +
              (double)nm1d2;
            Flattop->data[nm1d2 + 1] = apnd - (double)nm1d2;
          }
        }
      }
    }

    if (rtIsNaN(Flattop->data[Flattop->size[1] - 1] + 1.0)) {
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Decay, i0, sizeof(double));
      Decay->data[0] = rtNaN;
    } else if (1821.0 < Flattop->data[Flattop->size[1] - 1] + 1.0) {
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)Decay, i0, sizeof(double));
    } else if (rtIsInf(Flattop->data[Flattop->size[1] - 1] + 1.0) &&
               (Flattop->data[Flattop->size[1] - 1] + 1.0 == 1821.0)) {
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Decay, i0, sizeof(double));
      Decay->data[0] = rtNaN;
    } else if (floor(Flattop->data[Flattop->size[1] - 1] + 1.0) == Flattop->
               data[Flattop->size[1] - 1] + 1.0) {
      mtmp = Flattop->data[Flattop->size[1] - 1] + 1.0;
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = (int)floor(1821.0 - mtmp) + 1;
      emxEnsureCapacity((emxArray__common *)Decay, i0, sizeof(double));
      k = (int)floor(1821.0 - mtmp);
      for (i0 = 0; i0 <= k; i0++) {
        Decay->data[Decay->size[0] * i0] = mtmp + (double)i0;
      }
    } else {
      ndbl = floor((1821.0 - (Flattop->data[Flattop->size[1] - 1] + 1.0)) + 0.5);
      apnd = (Flattop->data[Flattop->size[1] - 1] + 1.0) + ndbl;
      absa = fabs(Flattop->data[Flattop->size[1] - 1] + 1.0);
      if (!(absa > 1821.0)) {
        absa = 1821.0;
      }

      if (fabs(apnd - 1821.0) < 4.4408920985006262E-16 * absa) {
        ndbl++;
        apnd = 1821.0;
      } else if (apnd - 1821.0 > 0.0) {
        apnd = (Flattop->data[Flattop->size[1] - 1] + 1.0) + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        s = (int)ndbl;
      } else {
        s = 0;
      }

      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = s;
      emxEnsureCapacity((emxArray__common *)Decay, i0, sizeof(double));
      if (s > 0) {
        Decay->data[0] = Flattop->data[Flattop->size[1] - 1] + 1.0;
        if (s > 1) {
          Decay->data[s - 1] = apnd;
          nm1d2 = (s - 1) / 2;
          for (k = 1; k < nm1d2; k++) {
            Decay->data[k] = (Flattop->data[Flattop->size[1] - 1] + 1.0) +
              (double)k;
            Decay->data[(s - k) - 1] = apnd - (double)k;
          }

          if (nm1d2 << 1 == s - 1) {
            Decay->data[nm1d2] = ((Flattop->data[Flattop->size[1] - 1] + 1.0) +
                                  apnd) / 2.0;
          } else {
            Decay->data[nm1d2] = (Flattop->data[Flattop->size[1] - 1] + 1.0) +
              (double)nm1d2;
            Decay->data[nm1d2 + 1] = apnd - (double)nm1d2;
          }
        }
      }
    }
  } else {
    x = rt_roundd_snf(DELAY * fs * 1.0E-6);
    mtmp = rt_roundd_snf(DELAY * fs * 1.0E-6 + FILLING * fs * 1.0E-6);
    if (rtIsNaN(x) || rtIsNaN(mtmp)) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Rise, i0, sizeof(double));
      Rise->data[0] = rtNaN;
    } else if (mtmp < x) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)Rise, i0, sizeof(double));
    } else if ((rtIsInf(x) || rtIsInf(mtmp)) && (x == mtmp)) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Rise, i0, sizeof(double));
      Rise->data[0] = rtNaN;
    } else if (x == x) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = (int)(mtmp - x) + 1;
      emxEnsureCapacity((emxArray__common *)Rise, i0, sizeof(double));
      k = (int)(mtmp - x);
      for (i0 = 0; i0 <= k; i0++) {
        Rise->data[Rise->size[0] * i0] = x + (double)i0;
      }
    } else {
      ndbl = floor((mtmp - x) + 0.5);
      apnd = x + ndbl;
      cdiff = apnd - mtmp;
      absa = fabs(x);
      absb = fabs(mtmp);
      if ((absa > absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = mtmp;
      } else if (cdiff > 0.0) {
        apnd = x + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        s = (int)ndbl;
      } else {
        s = 0;
      }

      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = s;
      emxEnsureCapacity((emxArray__common *)Rise, i0, sizeof(double));
      if (s > 0) {
        Rise->data[0] = x;
        if (s > 1) {
          Rise->data[s - 1] = apnd;
          nm1d2 = (s - 1) / 2;
          for (k = 1; k < nm1d2; k++) {
            Rise->data[k] = x + (double)k;
            Rise->data[(s - k) - 1] = apnd - (double)k;
          }

          if (nm1d2 << 1 == s - 1) {
            Rise->data[nm1d2] = (x + apnd) / 2.0;
          } else {
            Rise->data[nm1d2] = x + (double)nm1d2;
            Rise->data[nm1d2 + 1] = apnd - (double)nm1d2;
          }
        }
      }
    }

    d = (Rise->data[Rise->size[1] - 1] + 1.0) + rt_roundd_snf(FLATTOP * fs *
      1.0E-6);
    if (rtIsNaN(Rise->data[Rise->size[1] - 1] + 1.0) || rtIsNaN(d)) {
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Flattop, i0, sizeof(double));
      Flattop->data[0] = rtNaN;
    } else if (d < Rise->data[Rise->size[1] - 1] + 1.0) {
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)Flattop, i0, sizeof(double));
    } else if ((rtIsInf(Rise->data[Rise->size[1] - 1] + 1.0) || rtIsInf(d)) &&
               (Rise->data[Rise->size[1] - 1] + 1.0 == d)) {
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Flattop, i0, sizeof(double));
      Flattop->data[0] = rtNaN;
    } else if (floor(Rise->data[Rise->size[1] - 1] + 1.0) == Rise->data
               [Rise->size[1] - 1] + 1.0) {
      mtmp = Rise->data[Rise->size[1] - 1] + 1.0;
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = (int)floor(d - mtmp) + 1;
      emxEnsureCapacity((emxArray__common *)Flattop, i0, sizeof(double));
      k = (int)floor(d - mtmp);
      for (i0 = 0; i0 <= k; i0++) {
        Flattop->data[Flattop->size[0] * i0] = mtmp + (double)i0;
      }
    } else {
      ndbl = floor((d - (Rise->data[Rise->size[1] - 1] + 1.0)) + 0.5);
      apnd = (Rise->data[Rise->size[1] - 1] + 1.0) + ndbl;
      cdiff = apnd - d;
      absa = fabs(Rise->data[Rise->size[1] - 1] + 1.0);
      absb = fabs(d);
      if ((absa > absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = d;
      } else if (cdiff > 0.0) {
        apnd = (Rise->data[Rise->size[1] - 1] + 1.0) + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        s = (int)ndbl;
      } else {
        s = 0;
      }

      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = s;
      emxEnsureCapacity((emxArray__common *)Flattop, i0, sizeof(double));
      if (s > 0) {
        Flattop->data[0] = Rise->data[Rise->size[1] - 1] + 1.0;
        if (s > 1) {
          Flattop->data[s - 1] = apnd;
          nm1d2 = (s - 1) / 2;
          for (k = 1; k < nm1d2; k++) {
            Flattop->data[k] = (Rise->data[Rise->size[1] - 1] + 1.0) + (double)k;
            Flattop->data[(s - k) - 1] = apnd - (double)k;
          }

          if (nm1d2 << 1 == s - 1) {
            Flattop->data[nm1d2] = ((Rise->data[Rise->size[1] - 1] + 1.0) + apnd)
              / 2.0;
          } else {
            Flattop->data[nm1d2] = (Rise->data[Rise->size[1] - 1] + 1.0) +
              (double)nm1d2;
            Flattop->data[nm1d2 + 1] = apnd - (double)nm1d2;
          }
        }
      }
    }

    if (rtIsNaN(Flattop->data[Flattop->size[1] - 1] + 1.0)) {
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Decay, i0, sizeof(double));
      Decay->data[0] = rtNaN;
    } else if (16384.0 < Flattop->data[Flattop->size[1] - 1] + 1.0) {
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)Decay, i0, sizeof(double));
    } else if (rtIsInf(Flattop->data[Flattop->size[1] - 1] + 1.0) &&
               (Flattop->data[Flattop->size[1] - 1] + 1.0 == 16384.0)) {
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Decay, i0, sizeof(double));
      Decay->data[0] = rtNaN;
    } else if (floor(Flattop->data[Flattop->size[1] - 1] + 1.0) == Flattop->
               data[Flattop->size[1] - 1] + 1.0) {
      mtmp = Flattop->data[Flattop->size[1] - 1] + 1.0;
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = (int)floor(16384.0 - mtmp) + 1;
      emxEnsureCapacity((emxArray__common *)Decay, i0, sizeof(double));
      k = (int)floor(16384.0 - mtmp);
      for (i0 = 0; i0 <= k; i0++) {
        Decay->data[Decay->size[0] * i0] = mtmp + (double)i0;
      }
    } else {
      ndbl = floor((16384.0 - (Flattop->data[Flattop->size[1] - 1] + 1.0)) + 0.5);
      apnd = (Flattop->data[Flattop->size[1] - 1] + 1.0) + ndbl;
      absa = fabs(Flattop->data[Flattop->size[1] - 1] + 1.0);
      if (!(absa > 16384.0)) {
        absa = 16384.0;
      }

      if (fabs(apnd - 16384.0) < 4.4408920985006262E-16 * absa) {
        ndbl++;
        apnd = 16384.0;
      } else if (apnd - 16384.0 > 0.0) {
        apnd = (Flattop->data[Flattop->size[1] - 1] + 1.0) + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        s = (int)ndbl;
      } else {
        s = 0;
      }

      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = s;
      emxEnsureCapacity((emxArray__common *)Decay, i0, sizeof(double));
      if (s > 0) {
        Decay->data[0] = Flattop->data[Flattop->size[1] - 1] + 1.0;
        if (s > 1) {
          Decay->data[s - 1] = apnd;
          nm1d2 = (s - 1) / 2;
          for (k = 1; k < nm1d2; k++) {
            Decay->data[k] = (Flattop->data[Flattop->size[1] - 1] + 1.0) +
              (double)k;
            Decay->data[(s - k) - 1] = apnd - (double)k;
          }

          if (nm1d2 << 1 == s - 1) {
            Decay->data[nm1d2] = ((Flattop->data[Flattop->size[1] - 1] + 1.0) +
                                  apnd) / 2.0;
          } else {
            Decay->data[nm1d2] = (Flattop->data[Flattop->size[1] - 1] + 1.0) +
              (double)nm1d2;
            Decay->data[nm1d2 + 1] = apnd - (double)nm1d2;
          }
        }
      }
    }
  }

  s = 0;
  emxInit_real_T1(&idxP, 1);
  emxInit_real_T1(&dw, 1);
  emxInit_boolean_T(&b_x, 1);
  emxInit_int32_T(&ii, 1);
  emxInit_boolean_T(&b_RP, 1);
  emxInit_boolean_T(&b_PP, 1);
  do {
    exitg1 = 0;
    if (60 > PP->size[0]) {
      i0 = 0;
      i1 = 0;
    } else {
      i0 = 59;
      i1 = PP->size[0];
    }

    idx = b_PP->size[0];
    b_PP->size[0] = i1 - i0;
    emxEnsureCapacity((emxArray__common *)b_PP, idx, sizeof(boolean_T));
    k = i1 - i0;
    for (i1 = 0; i1 < k; i1++) {
      b_PP->data[i1] = (PP->data[i0 + i1] == 0.0);
    }

    guard1 = false;
    if (sum(b_PP) > 0.0) {
      guard1 = true;
    } else {
      for (i0 = 0; i0 < 1361; i0++) {
        b_FP[i0] = (FP->data[iv0[i0] - 1] == 0.0);
      }

      if (b_sum(b_FP) > 0.0) {
        guard1 = true;
      } else {
        if (60 > RP->size[0]) {
          i0 = 0;
          i1 = 0;
        } else {
          i0 = 59;
          i1 = RP->size[0];
        }

        idx = b_RP->size[0];
        b_RP->size[0] = i1 - i0;
        emxEnsureCapacity((emxArray__common *)b_RP, idx, sizeof(boolean_T));
        k = i1 - i0;
        for (i1 = 0; i1 < k; i1++) {
          b_RP->data[i1] = (RP->data[i0 + i1] == 0.0);
        }

        if (sum(b_RP) > 0.0) {
          guard1 = true;
        } else {
          exitg1 = 1;
        }
      }
    }

    if (guard1) {
      if (60 > PP->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = PP->size[0];
      }

      idx = b_x->size[0];
      b_x->size[0] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)b_x, idx, sizeof(boolean_T));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        b_x->data[i1] = (PP->data[i0 + i1] == 0.0);
      }

      nm1d2 = b_x->size[0];
      idx = 0;
      i0 = ii->size[0];
      ii->size[0] = b_x->size[0];
      emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
      k = 1;
      exitg2 = false;
      while ((!exitg2) && (k <= nm1d2)) {
        if (b_x->data[k - 1]) {
          idx++;
          ii->data[idx - 1] = k;
          if (idx >= nm1d2) {
            exitg2 = true;
          } else {
            k++;
          }
        } else {
          k++;
        }
      }

      if (b_x->size[0] == 1) {
        if (idx == 0) {
          i0 = ii->size[0];
          ii->size[0] = 0;
          emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
        }
      } else {
        i0 = ii->size[0];
        if (1 > idx) {
          ii->size[0] = 0;
        } else {
          ii->size[0] = idx;
        }

        emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
      }

      i0 = idxP->size[0];
      idxP->size[0] = ii->size[0];
      emxEnsureCapacity((emxArray__common *)idxP, i0, sizeof(double));
      k = ii->size[0];
      for (i0 = 0; i0 < k; i0++) {
        idxP->data[i0] = ii->data[i0];
      }

      i0 = ii->size[0];
      ii->size[0] = idxP->size[0];
      emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
      k = idxP->size[0];
      for (i0 = 0; i0 < k; i0++) {
        ii->data[i0] = (int)((60.0 + idxP->data[i0]) - 1.0);
      }

      i0 = dw->size[0];
      dw->size[0] = idxP->size[0];
      emxEnsureCapacity((emxArray__common *)dw, i0, sizeof(double));
      k = idxP->size[0];
      for (i0 = 0; i0 < k; i0++) {
        dw->data[i0] = PP->data[(int)((60.0 + idxP->data[i0]) - 2.0) - 1];
      }

      k = dw->size[0];
      for (i0 = 0; i0 < k; i0++) {
        PP->data[ii->data[i0] - 1] = dw->data[i0];
      }

      for (i0 = 0; i0 < 1361; i0++) {
        b_FP[i0] = (FP->data[59 + i0] == 0.0);
      }

      idx = 0;
      k = 1;
      exitg2 = false;
      while ((!exitg2) && (k < 1362)) {
        if (b_FP[k - 1]) {
          idx++;
          ii_data[idx - 1] = (short)k;
          if (idx >= 1361) {
            exitg2 = true;
          } else {
            k++;
          }
        } else {
          k++;
        }
      }

      if (1 > idx) {
        k = 0;
        nm1d2 = 0;
      } else {
        k = idx;
        nm1d2 = idx;
      }

      for (i0 = 0; i0 < k; i0++) {
        idxF_data[i0] = ii_data[i0];
      }

      for (i0 = 0; i0 < nm1d2; i0++) {
        ii_data[i0] = (short)(idxF_data[i0] + 59);
      }

      for (i0 = 0; i0 < nm1d2; i0++) {
        tmp_data[i0] = FP->data[idxF_data[i0] + 57];
      }

      for (i0 = 0; i0 < k; i0++) {
        FP->data[ii_data[i0] - 1] = tmp_data[i0];
      }

      if (60 > RP->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = RP->size[0];
      }

      idx = b_x->size[0];
      b_x->size[0] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)b_x, idx, sizeof(boolean_T));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        b_x->data[i1] = (RP->data[i0 + i1] == 0.0);
      }

      nm1d2 = b_x->size[0];
      idx = 0;
      i0 = ii->size[0];
      ii->size[0] = b_x->size[0];
      emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
      k = 1;
      exitg2 = false;
      while ((!exitg2) && (k <= nm1d2)) {
        if (b_x->data[k - 1]) {
          idx++;
          ii->data[idx - 1] = k;
          if (idx >= nm1d2) {
            exitg2 = true;
          } else {
            k++;
          }
        } else {
          k++;
        }
      }

      if (b_x->size[0] == 1) {
        if (idx == 0) {
          i0 = ii->size[0];
          ii->size[0] = 0;
          emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
        }
      } else {
        i0 = ii->size[0];
        if (1 > idx) {
          ii->size[0] = 0;
        } else {
          ii->size[0] = idx;
        }

        emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
      }

      i0 = idxP->size[0];
      idxP->size[0] = ii->size[0];
      emxEnsureCapacity((emxArray__common *)idxP, i0, sizeof(double));
      k = ii->size[0];
      for (i0 = 0; i0 < k; i0++) {
        idxP->data[i0] = ii->data[i0];
      }

      i0 = ii->size[0];
      ii->size[0] = idxP->size[0];
      emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
      k = idxP->size[0];
      for (i0 = 0; i0 < k; i0++) {
        ii->data[i0] = (int)((60.0 + idxP->data[i0]) - 1.0);
      }

      i0 = dw->size[0];
      dw->size[0] = idxP->size[0];
      emxEnsureCapacity((emxArray__common *)dw, i0, sizeof(double));
      k = idxP->size[0];
      for (i0 = 0; i0 < k; i0++) {
        dw->data[i0] = RP->data[(int)((60.0 + idxP->data[i0]) - 2.0) - 1];
      }

      k = dw->size[0];
      for (i0 = 0; i0 < k; i0++) {
        RP->data[ii->data[i0] - 1] = dw->data[i0];
      }

      s++;
      if (s > 1820) {
        exitg1 = 1;
      }
    }
  } while (exitg1 == 0);

  emxFree_boolean_T(&b_PP);
  emxFree_boolean_T(&b_RP);
  emxInit_real_T1(&b_FA, 1);
  i0 = b_FA->size[0];
  b_FA->size[0] = Rise->size[1];
  emxEnsureCapacity((emxArray__common *)b_FA, i0, sizeof(double));
  k = Rise->size[1];
  for (i0 = 0; i0 < k; i0++) {
    b_FA->data[i0] = FA->data[(int)Rise->data[Rise->size[0] * i0] - 1];
  }

  emxInit_real_T(&y, 2);
  emxInit_creal_T(&y_mC, 1);
  emxInit_real_T(&res_full_mean, 2);
  emxInit_real_T2(&res_full_variance, 3);
  emxInit_creal_T(&u_mCal, 1);
  emxInit_creal_T(&r_mCal, 1);
  emxInit_int32_T(&r0, 1);
  emxInit_real_T(&r1, 2);
  emxInit_boolean_T(&c_FP, 1);
  emxInit_creal_T(&b_u_mCal, 1);
  emxInit_creal_T(&c_u_mCal, 1);
  emxInit_real_T1(&b_PA, 1);
  emxInit_real_T1(&b_dw, 1);
  emxInit_real_T1(&b_s_max_dw, 1);
  emxInit_real_T1(&c_s_max_dw, 1);
  emxInit_real_T1(&d_s_max_dw, 1);
  emxInit_boolean_T(&e_s_max_dw, 1);
  emxInit_real_T(&c_dw, 2);
  emxInit_creal_T(&d_u_mCal, 1);
  emxInit_creal_T(&b_y_mC, 1);
  emxInit_creal_T(&c_FA, 1);
  emxInit_creal_T(&b_RA, 1);
  emxInit_real_T1(&b_s_max_UKF_dwfix, 1);
  emxInit_real_T1(&c_s_max_UKF_dwfix, 1);
  emxInit_real_T1(&d_s_max_UKF_dwfix, 1);
  emxInit_boolean_T(&e_s_max_UKF_dwfix, 1);
  emxInit_real_T1(&b_s_max_UKF, 1);
  emxInit_real_T1(&c_s_max_UKF, 1);
  emxInit_real_T1(&d_s_max_UKF, 1);
  emxInit_boolean_T(&e_s_max_UKF, 1);
  emxInit_real_T1(&b_s_max_PS1, 1);
  emxInit_real_T1(&c_s_max_PS1, 1);
  emxInit_real_T1(&d_s_max_PS1, 1);
  emxInit_boolean_T(&e_s_max_PS1, 1);
  emxInit_real_T(&b_idxP, 2);
  emxInit_real_T(&b_res_full_mean, 2);
  emxInit_real_T(&c_res_full_mean, 2);
  emxInit_real_T(&d_res_full_mean, 2);
  emxInit_real_T(&e_res_full_mean, 2);
  emxInit_real_T(&f_res_full_mean, 2);
  emxInit_real_T1(&c_PA, 1);
  b_guard1 = false;
  if (mean(b_FA) > 3.0) {
    i0 = c_PA->size[0];
    c_PA->size[0] = Flattop->size[1];
    emxEnsureCapacity((emxArray__common *)c_PA, i0, sizeof(double));
    k = Flattop->size[1];
    for (i0 = 0; i0 < k; i0++) {
      c_PA->data[i0] = PA->data[(int)Flattop->data[Flattop->size[0] * i0] - 1];
    }

    if ((mean(c_PA) > 3.0) && (!(s > 1820))) {
      /*     %% Unscented Kalman Filter Residual Generation + GLRT Evaluation */
      c_f_generate_online_UKF_residua(PA, PP, FA, FP, RA, RP, FS, cal_coeff,
        tau_m, K_m, X0, QL_nom, MeasNoiseVar, ProcessVar, res_full_mean,
        res_full_variance);
      nm1d2 = res_full_mean->size[1];
      if (2 > nm1d2) {
        nm1d2 = 2;
      }

      if (res_full_mean->size[1] == 0) {
        s = 0;
      } else {
        s = nm1d2;
      }

      i0 = y->size[0] * y->size[1];
      y->size[0] = 2;
      y->size[1] = s;
      emxEnsureCapacity((emxArray__common *)y, i0, sizeof(double));
      k = s << 1;
      for (i0 = 0; i0 < k; i0++) {
        y->data[i0] = 0.0;
      }

      nm1d2 = res_full_mean->size[1];
      if (2 > nm1d2) {
        nm1d2 = 2;
      }

      if (res_full_mean->size[1] == 0) {
        s = 0;
      } else {
        s = nm1d2;
      }

      for (k = 0; k < s; k++) {
        for (i0 = 0; i0 < 2; i0++) {
          y->data[i0 + y->size[0] * k] = res_full_mean->data[i0 +
            res_full_mean->size[0] * k] - r_mean_nom_UKF[i0];
        }
      }

      /*      figure(9) */
      /*      plot(res_full_mean(1,45:end), res_full_mean(2,45:end), '.') */
      /*      hold on */
      f_GLT(Sigma_nom_UKF, y, r1);
      i0 = s_max_UKF->size[0];
      s_max_UKF->size[0] = r1->size[1];
      emxEnsureCapacity((emxArray__common *)s_max_UKF, i0, sizeof(double));
      k = r1->size[1];
      for (i0 = 0; i0 < k; i0++) {
        s_max_UKF->data[i0] = r1->data[r1->size[0] * i0];
      }

      if (60 > res_full_mean->size[1]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = res_full_mean->size[1];
      }

      idx = f_res_full_mean->size[0] * f_res_full_mean->size[1];
      f_res_full_mean->size[0] = 1;
      f_res_full_mean->size[1] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)f_res_full_mean, idx, sizeof(double));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        f_res_full_mean->data[f_res_full_mean->size[0] * i1] =
          res_full_mean->data[res_full_mean->size[0] * (i0 + i1)];
      }

      b_rm_I = b_mean(f_res_full_mean);
      if (60 > res_full_mean->size[1]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = res_full_mean->size[1];
      }

      idx = e_res_full_mean->size[0] * e_res_full_mean->size[1];
      e_res_full_mean->size[0] = 1;
      e_res_full_mean->size[1] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)e_res_full_mean, idx, sizeof(double));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        e_res_full_mean->data[e_res_full_mean->size[0] * i1] =
          res_full_mean->data[1 + res_full_mean->size[0] * (i0 + i1)];
      }

      b_rm_Q = b_mean(e_res_full_mean);
      if (60 > res_full_mean->size[1]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = res_full_mean->size[1];
      }

      idx = d_res_full_mean->size[0] * d_res_full_mean->size[1];
      d_res_full_mean->size[0] = i1 - i0;
      d_res_full_mean->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)d_res_full_mean, idx, sizeof(double));
      k = i1 - i0;
      for (i1 = 0; i1 < 2; i1++) {
        for (idx = 0; idx < k; idx++) {
          d_res_full_mean->data[idx + d_res_full_mean->size[0] * i1] =
            res_full_mean->data[i1 + res_full_mean->size[0] * (i0 + idx)];
        }
      }

      cov(d_res_full_mean, res_var_data, res_var_size);
      b_rvar_1 = res_var_data[0];
      b_rvar_2 = res_var_data[1];
      b_rvar_3 = res_var_data[2];

      /*     %% */
      for (i0 = 0; i0 < 2; i0++) {
        for (i1 = 0; i1 < 2; i1++) {
          res_var_data[i1 + (i0 << 1)] = ProcessVar[i1 + 6 * i0] * alpha;
        }
      }

      d_f_generate_online_UKF_residua(PA, PP, FA, FP, RA, RP, FS, cal_coeff,
        dwfix, QL_nom, MeasNoiseVar, res_var_data, res_full_mean,
        res_full_variance);
      nm1d2 = res_full_mean->size[1];
      if (2 > nm1d2) {
        nm1d2 = 2;
      }

      if (res_full_mean->size[1] == 0) {
        s = 0;
      } else {
        s = nm1d2;
      }

      i0 = y->size[0] * y->size[1];
      y->size[0] = 2;
      y->size[1] = s;
      emxEnsureCapacity((emxArray__common *)y, i0, sizeof(double));
      k = s << 1;
      for (i0 = 0; i0 < k; i0++) {
        y->data[i0] = 0.0;
      }

      nm1d2 = res_full_mean->size[1];
      if (2 > nm1d2) {
        nm1d2 = 2;
      }

      if (res_full_mean->size[1] == 0) {
        s = 0;
      } else {
        s = nm1d2;
      }

      for (k = 0; k < s; k++) {
        for (i0 = 0; i0 < 2; i0++) {
          y->data[i0 + y->size[0] * k] = res_full_mean->data[i0 +
            res_full_mean->size[0] * k] - r_mean_nom_UKF_dwfix[i0];
        }
      }

      /*      figure(9) */
      /*      plot(res_full_mean_dwfix(1,45:end), res_full_mean_dwfix(2,45:end), '.') */
      /*      hold on */
      f_GLT(Sigma_nom_UKF_dwfix, y, r1);
      i0 = s_max_UKF_dwfix->size[0];
      s_max_UKF_dwfix->size[0] = r1->size[1];
      emxEnsureCapacity((emxArray__common *)s_max_UKF_dwfix, i0, sizeof(double));
      k = r1->size[1];
      for (i0 = 0; i0 < k; i0++) {
        s_max_UKF_dwfix->data[i0] = r1->data[r1->size[0] * i0];
      }

      if (60 > res_full_mean->size[1]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = res_full_mean->size[1];
      }

      idx = c_res_full_mean->size[0] * c_res_full_mean->size[1];
      c_res_full_mean->size[0] = 1;
      c_res_full_mean->size[1] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)c_res_full_mean, idx, sizeof(double));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        c_res_full_mean->data[c_res_full_mean->size[0] * i1] =
          res_full_mean->data[res_full_mean->size[0] * (i0 + i1)];
      }

      b_rm_I_dwfix = b_mean(c_res_full_mean);
      if (60 > res_full_mean->size[1]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = res_full_mean->size[1];
      }

      idx = b_res_full_mean->size[0] * b_res_full_mean->size[1];
      b_res_full_mean->size[0] = 1;
      b_res_full_mean->size[1] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)b_res_full_mean, idx, sizeof(double));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        b_res_full_mean->data[b_res_full_mean->size[0] * i1] =
          res_full_mean->data[1 + res_full_mean->size[0] * (i0 + i1)];
      }

      b_rm_Q_dwfix = b_mean(b_res_full_mean);

      /*     %% Parity Space Residual Genertation + GLRT Evaluation */
      c_f_generate_online_parityRes1_(PA, PP, FA, FP, RP, FS, QL_nom, idxP);
      c_f_generate_online_parityRes2_(PA, PP, FA, FP, RA, RP, FS, cal_coeff,
        tau_m, K_m, QL_nom, res_PS2);
      i0 = b_idxP->size[0] * b_idxP->size[1];
      b_idxP->size[0] = 1;
      b_idxP->size[1] = idxP->size[0];
      emxEnsureCapacity((emxArray__common *)b_idxP, i0, sizeof(double));
      k = idxP->size[0];
      for (i0 = 0; i0 < k; i0++) {
        b_idxP->data[b_idxP->size[0] * i0] = idxP->data[i0] - r_PS1_nom->data[i0];
      }

      b_f_GLT(Sigma_nom_PS1, b_idxP, r1);
      i0 = s_max_PS1->size[0];
      s_max_PS1->size[0] = r1->size[1];
      emxEnsureCapacity((emxArray__common *)s_max_PS1, i0, sizeof(double));
      k = r1->size[1];
      for (i0 = 0; i0 < k; i0++) {
        s_max_PS1->data[i0] = r1->data[r1->size[0] * i0];
      }

      if (60 > s_max_PS1->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_PS1->size[0];
      }

      idx = e_s_max_PS1->size[0];
      e_s_max_PS1->size[0] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)e_s_max_PS1, idx, sizeof(boolean_T));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        e_s_max_PS1->data[i1] = (s_max_PS1->data[i0 + i1] > 10.8);
      }

      b_classis_PS = sum(e_s_max_PS1);
      if (60 > s_max_PS1->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_PS1->size[0];
      }

      idx = d_s_max_PS1->size[0];
      d_s_max_PS1->size[0] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)d_s_max_PS1, idx, sizeof(double));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        d_s_max_PS1->data[i1] = s_max_PS1->data[i0 + i1];
      }

      b_strengthis_PS = mean(d_s_max_PS1);
      if (60 > s_max_PS1->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_PS1->size[0];
      }

      nm1d2 = 1;
      s = i1 - i0;
      c_mtmp = s_max_PS1->data[i0];
      if (i1 - i0 > 1) {
        if (rtIsNaN(c_mtmp)) {
          idx = 2;
          exitg2 = false;
          while ((!exitg2) && (idx <= s)) {
            nm1d2 = idx;
            if (!rtIsNaN(s_max_PS1->data[(i0 + idx) - 1])) {
              c_mtmp = s_max_PS1->data[(i0 + idx) - 1];
              exitg2 = true;
            } else {
              idx++;
            }
          }
        }

        if (nm1d2 < i1 - i0) {
          for (idx = nm1d2 - 1; idx + 2 <= s; idx++) {
            if (s_max_PS1->data[(i0 + idx) + 1] > c_mtmp) {
              c_mtmp = s_max_PS1->data[(i0 + idx) + 1];
            }
          }
        }
      }

      if (60 > s_max_PS1->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_PS1->size[0];
      }

      idx = c_s_max_PS1->size[0];
      c_s_max_PS1->size[0] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)c_s_max_PS1, idx, sizeof(double));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        c_s_max_PS1->data[i1] = s_max_PS1->data[i0 + i1];
      }

      b_median_PS = median(c_s_max_PS1);
      if (60 > s_max_PS1->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_PS1->size[0];
      }

      if (i1 - i0 == 0) {
        c_M = rtNaN;
      } else {
        idx = idxP->size[0];
        idxP->size[0] = i1 - i0;
        emxEnsureCapacity((emxArray__common *)idxP, idx, sizeof(double));
        k = i1 - i0;
        for (i1 = 0; i1 < k; i1++) {
          idxP->data[i1] = s_max_PS1->data[i0 + i1];
        }

        sort(idxP);
        c_M = idxP->data[0];
        nm1d2 = 1;
        b_mtmp = idxP->data[0];
        idx = 1;
        for (k = 1; k - 1 < (int)((double)idxP->size[0] + -1.0); k++) {
          if (idxP->data[k] == b_mtmp) {
            idx++;
          } else {
            if (idx > nm1d2) {
              c_M = b_mtmp;
              nm1d2 = idx;
            }

            b_mtmp = idxP->data[k];
            idx = 1;
          }
        }

        if (idx > nm1d2) {
          c_M = b_mtmp;
        }
      }

      if (60 > s_max_PS1->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_PS1->size[0];
      }

      idx = b_s_max_PS1->size[0];
      b_s_max_PS1->size[0] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)b_s_max_PS1, idx, sizeof(double));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        b_s_max_PS1->data[i1] = s_max_PS1->data[i0 + i1];
      }

      b_var_PS = var(b_s_max_PS1);

      /*     %% Check if GLT is above a threshold. */
      if (60 > s_max_UKF->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_UKF->size[0];
      }

      idx = e_s_max_UKF->size[0];
      e_s_max_UKF->size[0] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)e_s_max_UKF, idx, sizeof(boolean_T));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        e_s_max_UKF->data[i1] = (s_max_UKF->data[i0 + i1] > 13.8);
      }

      b_classis_UKF = sum(e_s_max_UKF);
      if (60 > s_max_UKF->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_UKF->size[0];
      }

      idx = d_s_max_UKF->size[0];
      d_s_max_UKF->size[0] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)d_s_max_UKF, idx, sizeof(double));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        d_s_max_UKF->data[i1] = s_max_UKF->data[i0 + i1];
      }

      b_strengthis_UKF = mean(d_s_max_UKF);
      if (60 > s_max_UKF->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_UKF->size[0];
      }

      nm1d2 = 1;
      s = i1 - i0;
      b_mtmp = s_max_UKF->data[i0];
      if (i1 - i0 > 1) {
        if (rtIsNaN(b_mtmp)) {
          idx = 2;
          exitg2 = false;
          while ((!exitg2) && (idx <= s)) {
            nm1d2 = idx;
            if (!rtIsNaN(s_max_UKF->data[(i0 + idx) - 1])) {
              b_mtmp = s_max_UKF->data[(i0 + idx) - 1];
              exitg2 = true;
            } else {
              idx++;
            }
          }
        }

        if (nm1d2 < i1 - i0) {
          for (idx = nm1d2 - 1; idx + 2 <= s; idx++) {
            if (s_max_UKF->data[(i0 + idx) + 1] > b_mtmp) {
              b_mtmp = s_max_UKF->data[(i0 + idx) + 1];
            }
          }
        }
      }

      if (60 > s_max_UKF->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_UKF->size[0];
      }

      idx = c_s_max_UKF->size[0];
      c_s_max_UKF->size[0] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)c_s_max_UKF, idx, sizeof(double));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        c_s_max_UKF->data[i1] = s_max_UKF->data[i0 + i1];
      }

      b_median_UKF = median(c_s_max_UKF);
      if (60 > s_max_UKF->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_UKF->size[0];
      }

      if (i1 - i0 == 0) {
        M = rtNaN;
      } else {
        idx = idxP->size[0];
        idxP->size[0] = i1 - i0;
        emxEnsureCapacity((emxArray__common *)idxP, idx, sizeof(double));
        k = i1 - i0;
        for (i1 = 0; i1 < k; i1++) {
          idxP->data[i1] = s_max_UKF->data[i0 + i1];
        }

        sort(idxP);
        M = idxP->data[0];
        nm1d2 = 1;
        e_mtmp = idxP->data[0];
        idx = 1;
        for (k = 1; k - 1 < (int)((double)idxP->size[0] + -1.0); k++) {
          if (idxP->data[k] == e_mtmp) {
            idx++;
          } else {
            if (idx > nm1d2) {
              M = e_mtmp;
              nm1d2 = idx;
            }

            e_mtmp = idxP->data[k];
            idx = 1;
          }
        }

        if (idx > nm1d2) {
          M = e_mtmp;
        }
      }

      if (60 > s_max_UKF->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_UKF->size[0];
      }

      idx = b_s_max_UKF->size[0];
      b_s_max_UKF->size[0] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)b_s_max_UKF, idx, sizeof(double));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        b_s_max_UKF->data[i1] = s_max_UKF->data[i0 + i1];
      }

      b_var_UKF = var(b_s_max_UKF);
      if (60 > s_max_UKF_dwfix->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_UKF_dwfix->size[0];
      }

      idx = e_s_max_UKF_dwfix->size[0];
      e_s_max_UKF_dwfix->size[0] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)e_s_max_UKF_dwfix, idx, sizeof
                        (boolean_T));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        e_s_max_UKF_dwfix->data[i1] = (s_max_UKF_dwfix->data[i0 + i1] > 13.8);
      }

      b_classis_dwfix = sum(e_s_max_UKF_dwfix);
      if (60 > s_max_UKF_dwfix->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_UKF_dwfix->size[0];
      }

      idx = d_s_max_UKF_dwfix->size[0];
      d_s_max_UKF_dwfix->size[0] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)d_s_max_UKF_dwfix, idx, sizeof
                        (double));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        d_s_max_UKF_dwfix->data[i1] = s_max_UKF_dwfix->data[i0 + i1];
      }

      b_strengthis_dwfix = mean(d_s_max_UKF_dwfix);
      if (60 > s_max_UKF_dwfix->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_UKF_dwfix->size[0];
      }

      nm1d2 = 1;
      s = i1 - i0;
      e_mtmp = s_max_UKF_dwfix->data[i0];
      if (i1 - i0 > 1) {
        if (rtIsNaN(e_mtmp)) {
          idx = 2;
          exitg2 = false;
          while ((!exitg2) && (idx <= s)) {
            nm1d2 = idx;
            if (!rtIsNaN(s_max_UKF_dwfix->data[(i0 + idx) - 1])) {
              e_mtmp = s_max_UKF_dwfix->data[(i0 + idx) - 1];
              exitg2 = true;
            } else {
              idx++;
            }
          }
        }

        if (nm1d2 < i1 - i0) {
          for (idx = nm1d2 - 1; idx + 2 <= s; idx++) {
            if (s_max_UKF_dwfix->data[(i0 + idx) + 1] > e_mtmp) {
              e_mtmp = s_max_UKF_dwfix->data[(i0 + idx) + 1];
            }
          }
        }
      }

      if (60 > s_max_UKF_dwfix->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_UKF_dwfix->size[0];
      }

      idx = c_s_max_UKF_dwfix->size[0];
      c_s_max_UKF_dwfix->size[0] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)c_s_max_UKF_dwfix, idx, sizeof
                        (double));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        c_s_max_UKF_dwfix->data[i1] = s_max_UKF_dwfix->data[i0 + i1];
      }

      b_median_dwfix = median(c_s_max_UKF_dwfix);
      if (60 > s_max_UKF_dwfix->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_UKF_dwfix->size[0];
      }

      if (i1 - i0 == 0) {
        b_M = rtNaN;
      } else {
        idx = idxP->size[0];
        idxP->size[0] = i1 - i0;
        emxEnsureCapacity((emxArray__common *)idxP, idx, sizeof(double));
        k = i1 - i0;
        for (i1 = 0; i1 < k; i1++) {
          idxP->data[i1] = s_max_UKF_dwfix->data[i0 + i1];
        }

        sort(idxP);
        b_M = idxP->data[0];
        nm1d2 = 1;
        d_mtmp = idxP->data[0];
        idx = 1;
        for (k = 1; k - 1 < (int)((double)idxP->size[0] + -1.0); k++) {
          if (idxP->data[k] == d_mtmp) {
            idx++;
          } else {
            if (idx > nm1d2) {
              b_M = d_mtmp;
              nm1d2 = idx;
            }

            d_mtmp = idxP->data[k];
            idx = 1;
          }
        }

        if (idx > nm1d2) {
          b_M = d_mtmp;
        }
      }

      if (60 > s_max_UKF_dwfix->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_UKF_dwfix->size[0];
      }

      idx = b_s_max_UKF_dwfix->size[0];
      b_s_max_UKF_dwfix->size[0] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)b_s_max_UKF_dwfix, idx, sizeof
                        (double));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        b_s_max_UKF_dwfix->data[i1] = s_max_UKF_dwfix->data[i0 + i1];
      }

      b_var_dwfix = var(b_s_max_UKF_dwfix);

      /*     %% Get QL value and static detuning value */
      i0 = y_mC->size[0];
      y_mC->size[0] = PP->size[0];
      emxEnsureCapacity((emxArray__common *)y_mC, i0, sizeof(creal_T));
      k = PP->size[0];
      for (i0 = 0; i0 < k; i0++) {
        mtmp = 0.0 * PP->data[i0];
        ndbl = PP->data[i0];
        if (ndbl == 0.0) {
          d = mtmp / 180.0;
          mtmp = 0.0;
        } else if (mtmp == 0.0) {
          d = 0.0;
          mtmp = ndbl / 180.0;
        } else {
          d = mtmp / 180.0;
          mtmp = ndbl / 180.0;
        }

        y_mC->data[i0].re = 3.1415926535897931 * d;
        y_mC->data[i0].im = 3.1415926535897931 * mtmp;
      }

      b_exp(y_mC);
      i0 = y_mC->size[0];
      y_mC->size[0] = PA->size[0];
      emxEnsureCapacity((emxArray__common *)y_mC, i0, sizeof(creal_T));
      k = PA->size[0];
      for (i0 = 0; i0 < k; i0++) {
        y_mC->data[i0].re *= PA->data[i0];
        y_mC->data[i0].im *= PA->data[i0];
      }

      /*  Complex Probe measurement */
      i0 = u_mCal->size[0];
      u_mCal->size[0] = FP->size[0];
      emxEnsureCapacity((emxArray__common *)u_mCal, i0, sizeof(creal_T));
      k = FP->size[0];
      for (i0 = 0; i0 < k; i0++) {
        mtmp = 0.0 * FP->data[i0];
        ndbl = FP->data[i0];
        if (ndbl == 0.0) {
          d = mtmp / 180.0;
          mtmp = 0.0;
        } else if (mtmp == 0.0) {
          d = 0.0;
          mtmp = ndbl / 180.0;
        } else {
          d = mtmp / 180.0;
          mtmp = ndbl / 180.0;
        }

        u_mCal->data[i0].re = 3.1415926535897931 * d;
        u_mCal->data[i0].im = 3.1415926535897931 * mtmp;
      }

      b_exp(u_mCal);

      /*  Complex Forward measurement */
      i0 = r_mCal->size[0];
      r_mCal->size[0] = RP->size[0];
      emxEnsureCapacity((emxArray__common *)r_mCal, i0, sizeof(creal_T));
      k = RP->size[0];
      for (i0 = 0; i0 < k; i0++) {
        mtmp = 0.0 * RP->data[i0];
        ndbl = RP->data[i0];
        if (ndbl == 0.0) {
          d = mtmp / 180.0;
          mtmp = 0.0;
        } else if (mtmp == 0.0) {
          d = 0.0;
          mtmp = ndbl / 180.0;
        } else {
          d = mtmp / 180.0;
          mtmp = ndbl / 180.0;
        }

        r_mCal->data[i0].re = 3.1415926535897931 * d;
        r_mCal->data[i0].im = 3.1415926535897931 * mtmp;
      }

      b_exp(r_mCal);

      /*  Reflected */
      i0 = c_FA->size[0];
      c_FA->size[0] = FA->size[0];
      emxEnsureCapacity((emxArray__common *)c_FA, i0, sizeof(creal_T));
      k = FA->size[0];
      for (i0 = 0; i0 < k; i0++) {
        c_FA->data[i0].re = FA->data[i0] * u_mCal->data[i0].re;
        c_FA->data[i0].im = FA->data[i0] * u_mCal->data[i0].im;
      }

      i0 = b_RA->size[0];
      b_RA->size[0] = RA->size[0];
      emxEnsureCapacity((emxArray__common *)b_RA, i0, sizeof(creal_T));
      k = RA->size[0];
      for (i0 = 0; i0 < k; i0++) {
        b_RA->data[i0].re = RA->data[i0] * r_mCal->data[i0].re;
        b_RA->data[i0].im = RA->data[i0] * r_mCal->data[i0].im;
      }

      f_calibrateData(c_FA, b_RA, cal_coeff, u_mCal, r_mCal);
      i0 = b_y_mC->size[0];
      b_y_mC->size[0] = Flattop->size[1];
      emxEnsureCapacity((emxArray__common *)b_y_mC, i0, sizeof(creal_T));
      k = Flattop->size[1];
      for (i0 = 0; i0 < k; i0++) {
        b_y_mC->data[i0].re = y_mC->data[(int)Flattop->data[Flattop->size[0] *
          i0] - 1].re - (u_mCal->data[(int)Flattop->data[Flattop->size[0] * i0]
                         - 1].re + r_mCal->data[(int)Flattop->data[Flattop->
                         size[0] * i0] - 1].re);
        b_y_mC->data[i0].im = y_mC->data[(int)Flattop->data[Flattop->size[0] *
          i0] - 1].im - (u_mCal->data[(int)Flattop->data[Flattop->size[0] * i0]
                         - 1].im + r_mCal->data[(int)Flattop->data[Flattop->
                         size[0] * i0] - 1].im);
      }

      b_abs(b_y_mC, dw);
      if (mean(dw) < 0.05) {
        if (25 > Decay->size[1] - 1) {
          i0 = 0;
          i1 = 0;
        } else {
          i0 = 24;
          i1 = Decay->size[1] - 1;
        }

        idx = d_u_mCal->size[0];
        d_u_mCal->size[0] = i1 - i0;
        emxEnsureCapacity((emxArray__common *)d_u_mCal, idx, sizeof(creal_T));
        k = i1 - i0;
        for (i1 = 0; i1 < k; i1++) {
          d_u_mCal->data[i1] = u_mCal->data[(int)Decay->data[i0 + i1] - 1];
        }

        b_abs(d_u_mCal, dw);
        if (mean(dw) < 0.8) {
          b_calib_check = 1.0;
        } else {
          b_calib_check = 0.0;
        }
      } else {
        b_calib_check = 0.0;
      }

      x = f_computeQL(Rise, u_mCal, y_mC, fs, F0 * 1.0E+6);
      f_compute_detuning(y_mC, u_mCal, fs, x, dw);
      f_compute_detuning(y_mC, u_mCal, fs, QL_nom, dwfix);

      /*     %% Detuning Trace Residual Generation + GLRT Evaluation */
      if (45 > dw->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 44;
        i1 = dw->size[0];
      }

      if (45 > dwfix->size[0]) {
        idx = 0;
      } else {
        idx = 44;
      }

      nm1d2 = c_dw->size[0] * c_dw->size[1];
      c_dw->size[0] = 1;
      c_dw->size[1] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)c_dw, nm1d2, sizeof(double));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        c_dw->data[c_dw->size[0] * i1] = dw->data[i0 + i1] - dwfix->data[idx +
          i1];
      }

      b_f_GLT(Sigma_nom_dw, c_dw, r1);
      i0 = s_max_dw->size[0];
      s_max_dw->size[0] = r1->size[1];
      emxEnsureCapacity((emxArray__common *)s_max_dw, i0, sizeof(double));
      k = r1->size[1];
      for (i0 = 0; i0 < k; i0++) {
        s_max_dw->data[i0] = r1->data[r1->size[0] * i0];
      }

      if (60 > s_max_dw->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_dw->size[0];
      }

      idx = e_s_max_dw->size[0];
      e_s_max_dw->size[0] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)e_s_max_dw, idx, sizeof(boolean_T));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        e_s_max_dw->data[i1] = (s_max_dw->data[i0 + i1] > 10.8);
      }

      fs = sum(e_s_max_dw);
      if (60 > s_max_dw->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_dw->size[0];
      }

      idx = d_s_max_dw->size[0];
      d_s_max_dw->size[0] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)d_s_max_dw, idx, sizeof(double));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        d_s_max_dw->data[i1] = s_max_dw->data[i0 + i1];
      }

      b_strengthis_dw = mean(d_s_max_dw);
      if (60 > s_max_dw->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_dw->size[0];
      }

      nm1d2 = 1;
      s = i1 - i0;
      d_mtmp = s_max_dw->data[i0];
      if (i1 - i0 > 1) {
        if (rtIsNaN(d_mtmp)) {
          idx = 2;
          exitg2 = false;
          while ((!exitg2) && (idx <= s)) {
            nm1d2 = idx;
            if (!rtIsNaN(s_max_dw->data[(i0 + idx) - 1])) {
              d_mtmp = s_max_dw->data[(i0 + idx) - 1];
              exitg2 = true;
            } else {
              idx++;
            }
          }
        }

        if (nm1d2 < i1 - i0) {
          for (idx = nm1d2 - 1; idx + 2 <= s; idx++) {
            if (s_max_dw->data[(i0 + idx) + 1] > d_mtmp) {
              d_mtmp = s_max_dw->data[(i0 + idx) + 1];
            }
          }
        }
      }

      if (60 > s_max_dw->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_dw->size[0];
      }

      idx = c_s_max_dw->size[0];
      c_s_max_dw->size[0] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)c_s_max_dw, idx, sizeof(double));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        c_s_max_dw->data[i1] = s_max_dw->data[i0 + i1];
      }

      b_median_dw = median(c_s_max_dw);
      if (60 > s_max_dw->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_dw->size[0];
      }

      if (i1 - i0 == 0) {
        d_M = rtNaN;
      } else {
        idx = idxP->size[0];
        idxP->size[0] = i1 - i0;
        emxEnsureCapacity((emxArray__common *)idxP, idx, sizeof(double));
        k = i1 - i0;
        for (i1 = 0; i1 < k; i1++) {
          idxP->data[i1] = s_max_dw->data[i0 + i1];
        }

        sort(idxP);
        d_M = idxP->data[0];
        nm1d2 = 1;
        mtmp = idxP->data[0];
        idx = 1;
        for (k = 1; k - 1 < (int)((double)idxP->size[0] + -1.0); k++) {
          if (idxP->data[k] == mtmp) {
            idx++;
          } else {
            if (idx > nm1d2) {
              d_M = mtmp;
              nm1d2 = idx;
            }

            mtmp = idxP->data[k];
            idx = 1;
          }
        }

        if (idx > nm1d2) {
          d_M = mtmp;
        }
      }

      if (60 > s_max_dw->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 59;
        i1 = s_max_dw->size[0];
      }

      idx = b_s_max_dw->size[0];
      b_s_max_dw->size[0] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)b_s_max_dw, idx, sizeof(double));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        b_s_max_dw->data[i1] = s_max_dw->data[i0 + i1];
      }

      d = var(b_s_max_dw);

      /*     %% */
      i0 = b_dw->size[0];
      b_dw->size[0] = Flattop->size[1];
      emxEnsureCapacity((emxArray__common *)b_dw, i0, sizeof(double));
      k = Flattop->size[1];
      for (i0 = 0; i0 < k; i0++) {
        b_dw->data[i0] = dw->data[(int)Flattop->data[Flattop->size[0] * i0] - 1];
      }

      ndbl = mean(b_dw);
      i0 = b_PA->size[0];
      b_PA->size[0] = Flattop->size[1];
      emxEnsureCapacity((emxArray__common *)b_PA, i0, sizeof(double));
      k = Flattop->size[1];
      for (i0 = 0; i0 < k; i0++) {
        b_PA->data[i0] = PA->data[(int)Flattop->data[Flattop->size[0] * i0] - 1];
      }

      cdiff = mean(b_PA);
      i0 = c_u_mCal->size[0];
      c_u_mCal->size[0] = Rise->size[1];
      emxEnsureCapacity((emxArray__common *)c_u_mCal, i0, sizeof(creal_T));
      k = Rise->size[1];
      for (i0 = 0; i0 < k; i0++) {
        c_u_mCal->data[i0] = u_mCal->data[(int)Rise->data[Rise->size[0] * i0] -
          1];
      }

      b_abs(c_u_mCal, dw);
      apnd = mean(dw);
      k = u_mCal->size[0];
      i0 = b_u_mCal->size[0];
      b_u_mCal->size[0] = k;
      emxEnsureCapacity((emxArray__common *)b_u_mCal, i0, sizeof(creal_T));
      for (i0 = 0; i0 < k; i0++) {
        b_u_mCal->data[i0] = u_mCal->data[i0];
      }

      b_abs(b_u_mCal, dw);
      i0 = b_x->size[0];
      b_x->size[0] = dw->size[0];
      emxEnsureCapacity((emxArray__common *)b_x, i0, sizeof(boolean_T));
      k = dw->size[0];
      for (i0 = 0; i0 < k; i0++) {
        b_x->data[i0] = (dw->data[i0] < 1.5);
      }

      nm1d2 = b_x->size[0];
      idx = 0;
      i0 = ii->size[0];
      ii->size[0] = b_x->size[0];
      emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
      k = 1;
      exitg2 = false;
      while ((!exitg2) && (k <= nm1d2)) {
        if (b_x->data[k - 1]) {
          idx++;
          ii->data[idx - 1] = k;
          if (idx >= nm1d2) {
            exitg2 = true;
          } else {
            k++;
          }
        } else {
          k++;
        }
      }

      if (b_x->size[0] == 1) {
        if (idx == 0) {
          i0 = ii->size[0];
          ii->size[0] = 0;
          emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
        }
      } else {
        i0 = ii->size[0];
        if (1 > idx) {
          ii->size[0] = 0;
        } else {
          ii->size[0] = idx;
        }

        emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
      }

      i0 = idxP->size[0];
      idxP->size[0] = ii->size[0];
      emxEnsureCapacity((emxArray__common *)idxP, i0, sizeof(double));
      k = ii->size[0];
      for (i0 = 0; i0 < k; i0++) {
        idxP->data[i0] = ii->data[i0];
      }

      k = idxP->size[0] - 1;
      nm1d2 = 0;
      for (idx = 0; idx <= k; idx++) {
        if (idxP->data[idx] > (double)(unsigned int)Rise->data[0] + 3.0) {
          nm1d2++;
        }
      }

      i0 = r0->size[0];
      r0->size[0] = nm1d2;
      emxEnsureCapacity((emxArray__common *)r0, i0, sizeof(int));
      nm1d2 = 0;
      for (idx = 0; idx <= k; idx++) {
        if (idxP->data[idx] > (double)(unsigned int)Rise->data[0] + 3.0) {
          r0->data[nm1d2] = idx + 1;
          nm1d2++;
        }
      }

      absa = idxP->data[r0->data[0] - 1];

      /* double(abs(u_mCal(Flattop(end-1))) < 1); */
      absb = fabs(x - QL_nom);
      if (1420 > FP->size[0]) {
        i0 = 0;
        i1 = 0;
      } else {
        i0 = 1419;
        i1 = FP->size[0];
      }

      idx = c_FP->size[0];
      c_FP->size[0] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)c_FP, idx, sizeof(boolean_T));
      k = i1 - i0;
      for (i1 = 0; i1 < k; i1++) {
        c_FP->data[i1] = (FP->data[i0 + i1] == 0.0);
      }

      mtmp = sum(c_FP);
    } else {
      b_guard1 = true;
    }
  } else {
    b_guard1 = true;
  }

  if (b_guard1) {
    i0 = s_max_UKF->size[0];
    s_max_UKF->size[0] = PA->size[0];
    emxEnsureCapacity((emxArray__common *)s_max_UKF, i0, sizeof(double));
    k = PA->size[0];
    for (i0 = 0; i0 < k; i0++) {
      s_max_UKF->data[i0] = rtNaN;
    }

    i0 = s_max_UKF_dwfix->size[0];
    s_max_UKF_dwfix->size[0] = PA->size[0];
    emxEnsureCapacity((emxArray__common *)s_max_UKF_dwfix, i0, sizeof(double));
    k = PA->size[0];
    for (i0 = 0; i0 < k; i0++) {
      s_max_UKF_dwfix->data[i0] = rtNaN;
    }

    if (45 > dwfix->size[0]) {
      i0 = 1;
      i1 = 0;
    } else {
      i0 = 45;
      i1 = dwfix->size[0];
    }

    nm1d2 = i1 - i0;
    i0 = s_max_dw->size[0];
    s_max_dw->size[0] = nm1d2 + 1;
    emxEnsureCapacity((emxArray__common *)s_max_dw, i0, sizeof(double));
    for (i0 = 0; i0 <= nm1d2; i0++) {
      s_max_dw->data[i0] = rtNaN;
    }

    i0 = s_max_PS1->size[0];
    s_max_PS1->size[0] = r_PS1_nom->size[0];
    emxEnsureCapacity((emxArray__common *)s_max_PS1, i0, sizeof(double));
    k = r_PS1_nom->size[0];
    for (i0 = 0; i0 < k; i0++) {
      s_max_PS1->data[i0] = rtNaN;
    }

    i0 = res_PS2->size[0];
    res_PS2->size[0] = PA->size[0];
    emxEnsureCapacity((emxArray__common *)res_PS2, i0, sizeof(double));
    k = PA->size[0];
    for (i0 = 0; i0 < k; i0++) {
      res_PS2->data[i0] = rtNaN;
    }

    b_classis_UKF = rtNaN;
    b_classis_PS = rtNaN;
    fs = rtNaN;
    b_classis_dwfix = rtNaN;
    b_strengthis_UKF = rtNaN;
    b_strengthis_PS = rtNaN;
    b_strengthis_dw = rtNaN;
    b_strengthis_dwfix = rtNaN;
    b_mtmp = rtNaN;
    c_mtmp = rtNaN;
    d_mtmp = rtNaN;
    e_mtmp = rtNaN;
    b_median_UKF = rtNaN;
    b_median_PS = rtNaN;
    b_median_dw = rtNaN;
    b_median_dwfix = rtNaN;
    M = rtNaN;
    b_M = rtNaN;
    c_M = rtNaN;
    d_M = rtNaN;
    b_var_UKF = rtNaN;
    b_var_dwfix = rtNaN;
    b_var_PS = rtNaN;
    d = rtNaN;
    b_rm_I = rtNaN;
    b_rm_Q = rtNaN;
    b_rm_I_dwfix = rtNaN;
    b_rm_Q_dwfix = rtNaN;
    b_rvar_1 = rtNaN;
    b_rvar_2 = rtNaN;
    b_rvar_3 = rtNaN;
    x = rtNaN;
    ndbl = rtNaN;
    apnd = rtNaN;
    cdiff = rtNaN;
    absa = rtNaN;
    b_calib_check = rtNaN;
    absb = rtNaN;
    mtmp = rtNaN;
  }

  emxFree_real_T(&b_FA);
  emxFree_real_T(&c_PA);
  emxFree_real_T(&f_res_full_mean);
  emxFree_real_T(&e_res_full_mean);
  emxFree_real_T(&d_res_full_mean);
  emxFree_real_T(&c_res_full_mean);
  emxFree_real_T(&b_res_full_mean);
  emxFree_real_T(&b_idxP);
  emxFree_boolean_T(&e_s_max_PS1);
  emxFree_real_T(&d_s_max_PS1);
  emxFree_real_T(&c_s_max_PS1);
  emxFree_real_T(&b_s_max_PS1);
  emxFree_boolean_T(&e_s_max_UKF);
  emxFree_real_T(&d_s_max_UKF);
  emxFree_real_T(&c_s_max_UKF);
  emxFree_real_T(&b_s_max_UKF);
  emxFree_boolean_T(&e_s_max_UKF_dwfix);
  emxFree_real_T(&d_s_max_UKF_dwfix);
  emxFree_real_T(&c_s_max_UKF_dwfix);
  emxFree_real_T(&b_s_max_UKF_dwfix);
  emxFree_creal_T(&b_RA);
  emxFree_creal_T(&c_FA);
  emxFree_creal_T(&b_y_mC);
  emxFree_creal_T(&d_u_mCal);
  emxFree_real_T(&c_dw);
  emxFree_boolean_T(&e_s_max_dw);
  emxFree_real_T(&d_s_max_dw);
  emxFree_real_T(&c_s_max_dw);
  emxFree_real_T(&b_s_max_dw);
  emxFree_real_T(&b_dw);
  emxFree_real_T(&b_PA);
  emxFree_creal_T(&c_u_mCal);
  emxFree_creal_T(&b_u_mCal);
  emxFree_boolean_T(&c_FP);
  emxFree_real_T(&r1);
  emxFree_int32_T(&ii);
  emxFree_boolean_T(&b_x);
  emxFree_int32_T(&r0);
  emxFree_creal_T(&r_mCal);
  emxFree_creal_T(&u_mCal);
  emxFree_real_T(&res_full_variance);
  emxFree_real_T(&res_full_mean);
  emxFree_real_T(&dw);
  emxFree_creal_T(&y_mC);
  emxFree_real_T(&y);
  emxFree_real_T(&idxP);
  emxFree_real_T(&Decay);
  emxFree_real_T(&Flattop);
  emxFree_real_T(&Rise);

  /*  figure(14), */
  /*  hold on */
  /*  plot(dw,'') */
  /*  figure(21) */
  /*  hold on */
  /*  plot(res_full_mean(1,:),'k') */
  /*  plot(res_full_mean(2,:),'k') */
  /*  xlabel('Samples') */
  /*  ylabel('Residual') */
  /*  ylim([-0.05,0.05]) */
  /* [FIT, y_mC_hat]=f_cavitySystemSimulatior(y_mC, u_mC, f0, fs, sys_hat, QL, plt, u3) */
  *classis_UKF = b_classis_UKF;
  *classis_dwfix = b_classis_dwfix;
  *classis_PS = b_classis_PS;
  *classis_dw = fs;
  *strengthis_UKF = b_strengthis_UKF;
  *strengthis_dwfix = b_strengthis_dwfix;
  *strengthis_PS = b_strengthis_PS;
  *strengthis_dw = b_strengthis_dw;
  *max_UKF = b_mtmp;
  *max_dwfix = e_mtmp;
  *max_PS = c_mtmp;
  *max_dw = d_mtmp;
  *median_UKF = b_median_UKF;
  *median_dwfix = b_median_dwfix;
  *median_PS = b_median_PS;
  *median_dw = b_median_dw;
  *mode_UKF = M;
  *mode_dwfix = b_M;
  *mode_PS = c_M;
  *mode_dw = d_M;
  *var_UKF = b_var_UKF;
  *var_dwfix = b_var_dwfix;
  *var_PS = b_var_PS;
  *var_dw = d;
  *rm_I = b_rm_I;
  *rm_Q = b_rm_Q;
  *rm_I_dwfix = b_rm_I_dwfix;
  *rm_Q_dwfix = b_rm_Q_dwfix;
  *rvar_1 = b_rvar_1;
  *rvar_2 = b_rvar_2;
  *rvar_3 = b_rvar_3;
  *QL = x;
  *dw_stat = ndbl;
  *SP_F = apnd;
  *SP_P = cdiff;
  *PC = absa;
  *calib_check = b_calib_check;
  *dec_hq = absb;
  *zpth = mtmp;
}

/*
 * File trailer for f_generate_and_eval_multi_residuals_dwfix.c
 *
 * [EOF]
 */
