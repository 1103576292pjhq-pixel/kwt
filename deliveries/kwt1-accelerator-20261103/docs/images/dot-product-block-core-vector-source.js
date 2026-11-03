const fs=require('fs');
const root='D:/嵌赛芯片设计赛道/kwt1-a40-accelerator/docs/images/';
const a=[];
const esc=s=>String(s).replaceAll('&','&amp;').replaceAll('<','&lt;').replaceAll('>','&gt;');
a.push(`<svg xmlns="http://www.w3.org/2000/svg" width="2400" height="1500" viewBox="0 0 2400 1500"><title>四个RTL模块组成的单块点积计算核心</title><defs><linearGradient id="bg" x2="0" y2="1"><stop stop-color="#fff"/><stop offset="1" stop-color="#edf6ff"/></linearGradient><filter id="shadow" x="-20%" y="-20%" width="150%" height="160%"><feDropShadow dx="0" dy="5" stdDeviation="5" flood-color="#274b70" flood-opacity=".14"/></filter><marker id="blue" markerWidth="10" markerHeight="10" refX="8" refY="4" orient="auto"><path d="M0 0 L8 4 L0 8Z" fill="#1684c9"/></marker><marker id="orange" markerWidth="9" markerHeight="9" refX="8" refY="4" orient="auto"><path d="M0 0 L8 4 L0 8Z" fill="#de7a24"/></marker></defs><rect width="2400" height="1500" fill="url(#bg)"/>`);
function box(x,y,w,h,fill='#fff',stroke='#bfd4e5',r=18){a.push(`<rect x="${x}" y="${y}" width="${w}" height="${h}" rx="${r}" fill="${fill}" stroke="${stroke}" stroke-width="2" filter="url(#shadow)"/>`);}
function text(x,y,s,size=24,color='#173a59',anchor='start',bold=false){a.push(`<text x="${x}" y="${y}" fill="${color}" font-size="${size}" text-anchor="${anchor}" font-family="Microsoft YaHei, Noto Sans CJK SC, Arial, sans-serif" font-weight="${bold?700:400}">${esc(s)}</text>`);}
function path(d,control=false,width=4){a.push(`<path d="${d}" fill="none" stroke="${control?'#de7a24':'#1684c9'}" stroke-width="${width}" stroke-linecap="round" stroke-linejoin="round" ${control?'stroke-dasharray="9 7"':''} marker-end="url(#${control?'orange':'blue'})"/>`);}
text(1200,78,'一块点积，是怎样算出来的？',50,'#123958','middle',true);
text(1200,129,'4行 × 16列 · 16路乘法 · CTX4 · A40',27,'#53728c','middle');
box(280,180,1830,1000,'#f4faff','#63a6d8',26);
text(315,230,'④ 单块计算顶层 · dot_product_block_core.v',31,'#15517d','start',true);
const states=[['IDLE',340,155],['CLEAR',525,155],['RUN',710,155],['FLUSH',895,155],['QISSUE',1080,230],['QWAIT',1340,230],['DONE',1600,155]];
states.forEach(([s,x,w],i)=>{box(x,275,w,58,'#fff3e6','#edb676',12);text(x+w/2,313,s,25,'#9a4b0e','middle',true);if(i<states.length-1)path(`M${x+w+3} 304 H${states[i+1][1]-9}`,true,3);});
path('M1455 338 V365 H1195 V338',true,3);
text(1790,303,'输入计数跟随真实握手',18,'#9a4b0e');
text(1790,333,'先累加并排空，再量化',18,'#9a4b0e');
text(1200,406,'RUN只接收有序返回数据；FLUSH等待最后乘积真正写回acc',22,'#9a4b0e','middle');

box(25,430,225,240,'#e8f8fb','#4bafbd');
text(137,467,'4个X16 / Q12',23,'#087187','middle',true);
for(let p=0;p<4;p++){box(54,490+40*p,166,31,'#c4edf0','#5cbbc6',6);text(137,513+40*p,`X${p}   16位`,19,'#075565','middle');}
box(25,710,225,240,'#f2ecff','#a58ad5');
text(137,747,'4个W16 / Q16',23,'#63428c','middle',true);
for(let q=0;q<4;q++){box(54,770+40*q,166,31,'#e2d4f6','#ae91d0',6);text(137,793+40*q,`W${q}   16位`,19,'#56397c','middle');}
path('M250 550 H285 V585 H320');
path('M250 830 H285 V705 H320');
text(135,1000,'两条64位打包总线',19,'#46637b','middle');
text(135,1030,'一组是8个16位数',19,'#46637b','middle');
text(135,1060,'in_valid / in_ready',18,'#46637b','middle');

box(320,440,430,650,'#eaf5ff','#79b6df');
text(345,487,'① 16路乘法阵列',30,'#15517d','start',true);
text(345,525,'mul_array_4x4.v',22,'#46637b');
for(let q=0;q<4;q++)text(425+80*q,574,`W${q}`,20,'#75449e','middle');
for(let p=0;p<4;p++){text(350,625+70*p,`X${p}`,20,'#087187');for(let q=0;q<4;q++){box(395+80*q,590+70*p,60,55,'#baddf4','#5d9bc6',9);text(425+80*q,627+70*p,'×',28,'#174b72','middle',true);}}
text(535,925,'一级乘积寄存',23,'#15517d','middle',true);
for(let i=0;i<16;i++)box(355+i*22,945,18,43,'#efc9d5','#c9889d',4);
text(535,1032,'16个signed32乘积 · Q28',22,'#15517d','middle');
path('M750 800 H820');
text(783,758,'16路',18,'#1684c9','middle');
text(783,840,'32位',18,'#1684c9','middle');

box(820,440,600,650,'#eaf9f2','#77b9a0');
text(848,487,'② 四上下文累加',30,'#186d51','start',true);
text(848,525,'acc_context_bank.v',22,'#46637b');
const trays=[['g0',850,555,'#fce2eb','#d889a6'],['g1',1140,555,'#fff0d5','#d9aa55'],['g2',850,785,'#d8f2e3','#69af85'],['g3',1140,785,'#e5def9','#9d88cf']];
trays.forEach(([label,x,y,fill,stroke])=>{box(x,y,255,160,fill,stroke,12);text(x+16,y+31,label,25,'#214734','start',true);text(x+80,y+29,'16个acc40',17,'#46637b');for(let p=0;p<4;p++)for(let q=0;q<4;q++)box(x+25+50*q,y+45+25*p,40,19,fill,stroke,3);});
text(1120,756,'当前ctx选择一组写入，四组不互相求和',19,'#186d51','middle');
text(1120,996,'旧acc + 当前乘积 → 写回当前ctx',22,'#186d51','middle',true);
text(1120,1036,'合计64个acc40；每个输出累加64项',21,'#186d51','middle');
path('M1420 638 H1530');
text(1455,589,'选读',18,'#1684c9','middle');
text(1455,618,'acc40',16,'#1684c9','middle');

box(1490,440,580,650,'#fff8e9','#dfbc6b');
text(1517,487,'③ 单份偏置 / 量化',30,'#966011','start',true);
text(1517,525,'result_convert.v',22,'#46637b');
[['41位相加',600,'#dcedff'],['sat40',710,'#d8f2e3'],['RNE 右移16',820,'#fff0b3'],['sat16',930,'#e7defb']].forEach(([s,y,fill],i)=>{box(1530,y,300,75,fill,'#aabfc8',11);text(1680,y+47,s,29,'#274e61','middle',true);if(i<3)path(`M1680 ${y+77} V${y+101}`);});
path('M1420 638 H1530');
text(1855,672,'acc40 + bias32',18,'#46637b');
text(1855,753,'先sat40',20,'#46637b');
text(1855,850,'保留低16位',18,'#46637b');
text(1855,882,'正负取最近偶数',17,'#46637b');
text(1855,1012,'舍入后才sat16',18,'#46637b');
text(1520,1053,'global_last → flags[2]，不直接复用block_last',18,'#966011');

box(2140,250,230,175,'#fff2e4','#e7a96a');
text(2255,288,'外围bias寄存器',23,'#9a4b0e','middle',true);
for(let q=0;q<4;q++){box(2155+51*q,310,43,38,'#ffd6a2','#d89e59',6);text(2176+51*q,337,`B${q}`,18,'#9a4b0e','middle');}
text(2255,382,'共16列 · 每项signed32',17,'#9a4b0e','middle');
text(2255,410,'组合选读，不是移位寄存器',15,'#9a4b0e','middle');
path('M2110 265 H2140',true,3);
text(2255,229,'bias_addr = g×4+q',18,'#9a4b0e','middle');
path('M2255 425 V557 H1950 V638 H1834');
text(2040,544,'bias32 / Q28',18,'#1684c9','middle');

box(2140,640,230,375,'#eaf5ff','#79b6df');
text(2255,688,'逐项输出',28,'#15517d','middle',true);
text(2255,748,'Y16 / Q12',25,'#15517d','middle',true);
text(2255,786,'+ flags3',25,'#15517d','middle',true);
text(2255,846,'out_index',21,'#46637b','middle');
text(2255,880,'out_block_last',20,'#46637b','middle');
text(2255,938,'背压：Y、flags、位置',16,'#9a4b0e','middle');
text(2255,970,'一起保持',23,'#9a4b0e','middle',true);
path('M1830 968 H2093 V750 H2136');
path('M2255 1022 V1116 H1970',true,3);
text(2210,1150,'out_ready',19,'#9a4b0e','middle');
text(1120,1136,'数据：valid + ctx + row_mask + block_last 与乘积一起传递',20,'#15517d','middle');

const bottom=[['先算完整块','64个k × 4个ctx = 256组有效输入','最后乘积写回后，才开始转换','#eaf5ff'],['再逐项输出','普通块64项；尾行块48项','QISSUE / QWAIT：通常每两拍消费一项','#eaf9f2'],['下一块重复','前块量化完成后，再清零算后块','单套acc：乘加与前块量化不重叠','#fff2e4']];
bottom.forEach(([h,l1,l2,fill],i)=>{let x=40+i*790;box(x,1220,750,175,fill,'#bad0df');text(x+26,1268,`${i+1}  ${h}`,31,'#173a59','start',true);text(x+26,1321,l1,24);text(x+26,1361,l2,21,'#46637b');});
text(1200,1443,'独立编码示例：−4096 × 96 = −393216；其余63项与bias为0 → Y = −6',26,'#173a59','middle');
text(1200,1484,'依据当前RTL的功能图 · 组件已有验证证据，顶层尚未验证 · 非物理布局或频率承诺',17,'#6d8294','middle');
a.push('</svg>');
fs.writeFileSync(root+'kwt1-dot-product-block-core.svg',a.join('\n'),'utf8');
console.log('Editable SVG saved');
