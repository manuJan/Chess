isql /U SA   /P %3 /S %2 /i %1\Scripts\CreateCH.sql

isql /U SA   /P %3 /S %2 /d Chess /i %1\Scripts\GEntityModel.sql 
isql /U SA   /P %3 /S %2 /d Chess /i %1\Scripts\GTHEntityModel.sql 
isql /U SA   /P %3 /S %2 /d Chess /i %1\Scripts\GRTEntityModel.sql 
isql /U SA   /P %3 /S %2 /d Chess /i %1\Scripts\CHEntityModel.sql 

isql /U SA   /P %3 /S %2 /d Chess /i %1\Scripts\GRefModel.sql 
isql /U SA   /P %3 /S %2 /d Chess /i %1\Scripts\GTHRefModel.sql 
isql /U SA   /P %3 /S %2 /d Chess /i %1\Scripts\GRTRefModel.sql 
isql /U SA   /P %3 /S %2 /d Chess /i %1\Scripts\CHRefModel.sql 

cALL GLoadModel  %1 %2 %3 Chess
cALL GTHLoadModel  %1 %2 %3 Chess
cALL GRTLoadModel  %1 %2 %3 Chess
cALL CHLoadModel  %1 %2 %3 Chess
