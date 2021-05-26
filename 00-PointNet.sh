#!/bin/bash
echo "Read Only..."; exit 1
#/ ====================================================================== BEGIN FILE =====




./BuildWorldFile.py cf=Control.csv wf=/data/ARA/PointNet/PointCloud-ForumOfficeComplex.wf zone=17S






./PackPoly.py if=gt_label_forum_whole.ply \
              csv=/data/ARA/PointNet/PointCloud-ForumOfficeComplex.csv \
              bin=/data/ARA/PointNet/PointCloud-ForumOfficeComplex.bin \
              wf=/data/ARA/PointNet/PointCloud-ForumOfficeComplex.wf

./PackPoly.py if=pred_label_forum_whole.ply \
              csv=/data/ARA/PointNet/PointCloud-ForumOfficeComplex-pred.csv \
              bin=/data/ARA/PointNet/PointCloud-ForumOfficeComplex-pred.bin \
              wf=/data/ARA/PointNet/PointCloud-ForumOfficeComplex.wf










#/ ----- use ground truth data ----------------------------------------------






callisto/bin/PC2Horizon \
    gkb=/data/ARA/PointNet/HorizonAlt.bin \
    pc=/data/ARA/PointNet/PointCloud-ForumOfficeComplex.bin \
    lab=/data/ARA/PointNet/labels-groundtruth.txt \
    of=/data/ARA/PointNet/GroundTruth.GKB \
    ratio=1

time callisto/bin/PC2Horizon \
    gkb=/data/ARA/PointNet/HorizonAlt.bin \
    pc=/data/ARA/PointNet/PointCloud-ForumOfficeComplex-pred.bin \
    lab=/data/ARA/PointNet/labels-pred.txt \
    of=/data/ARA/PointNet/Prediction.GKB




callisto/bin/DisplayGKBHorizon \
    gkb=/data/ARA/PointNet/HorizonAlt.bin \
    hrz=/data/ARA/PointNet/Display-gkb.csv \
    ratio=.1 \
    mine=0 maxe=270 \
    mind=3 

callisto/bin/DisplayGKBHorizon \
    gkb=/data/ARA/PointNet/GroundTruth.GKB \
    hrz=/data/ARA/PointNet/Display-gt.csv \
    ratio=.1 \
    mine=0 maxe=270 \
    mind=3 

callisto/bin/DisplayGKBHorizon \
    gkb=/data/ARA/PointNet/Prediction.GKB \
    hrz=/data/ARA/PointNet/Display-pred.csv \
    ratio=.1 \
    mine=0 maxe=270 \
    mind=3 


ggobi /data/ARA/PointNet/Display-gkb.csv






#/ ======================================================================== END FILE =====
/data/ARA/PointNet/ForumComplex-GKB.bin
long.gkb.bin
