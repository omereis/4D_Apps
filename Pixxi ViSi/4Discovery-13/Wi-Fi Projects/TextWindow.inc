var twxpos;
var twypos;
var txtwin;
var txtf;
var txtb;
var txtx;
var twcurx;
var txty;
var twcury;
var txtw;
var txth;
var twframe;
var twframecol;
var twfh;
var twfw;
var twfont;
var twtext[255];
var twtxtcount;
var width;
var height;
var cmdtxtcount;
var txtbuf[1000];
var addCMDbuf := 1;
var twcolnum;
var twcl;
var fsh;
var twtxtc;
var CMDstring[1024];
var NLtoSpace;

func TWprint(var *pString)
  var pssize;
  pssize := strlen(pString);
  var ps;
  var p;
  var btemp;
  p := str_Ptr(pString);
  for(ps := 0; ps < pssize; ps ++)
  btemp := str_GetByte(p + ps);
  if(NLtoSpace && btemp == 10)
  btemp := 32;
  NLtoSpace := 0;
  endif
  TWwrite(btemp);
  next
endfunc

func TWprintVal(var value)
  var tempValString[50];
  to(tempValString);
  print(value);
  TWprint(tempValString);
endfunc

func TWwrite(var txtinput)

  drawChar2tw(twcurx, twcury, 32, txtf, txtb, twfont);

  var n;
  var o;
  var p;
  var chracc;
  chracc := txtw / (twfw);
  var chrdwn;
  chrdwn := txth / twfh;
  var apos;
  var skip2;
  skip2 := 0;

  if(txtinput > 31)

  if(addCMDbuf) twtext[twtxtcount] := txtinput;
  if(addCMDbuf) twtxtcount ++;
  drawChar2tw(twcurx, twcury, txtinput, /*twcolnum*/txtf, txtb, twfont);
  txtbuf[(chracc * twypos) + twxpos] := txtinput;
  //txfcol[(chracc * twypos) + twxpos] := twcolnum;
  twcurx := twcurx + twfw;
  twxpos ++;
  if((twcurx + twfw) > (txtw + txtx))
  twcury := twcury + twfh;
  twcurx := txtx;
  twypos ++;
  twxpos := 0;
  endif
  endif

  if(txtinput == 9)
  var tcnt; tcnt := 0;
  var ccpos; ccpos := twcurx / twfw;
  for(n := 0; n < (chracc / twfw); n++)
  tcnt := tcnt + twfh;
  if(tcnt > ccpos)
  for(o := 0; o < (tcnt - ccpos); o++)
  twcurx := twcurx + (twfw);
  twxpos ++;
  txtbuf[(chracc * twypos) + twxpos] := 32;
  //txfcol[(chracc * twypos) + twxpos] := twcolnum;
  next
  break;
  endif
  next
  endif

  //if(txtinput == 13 || txtinput == 10)
  if(txtinput == 13)
  twcury := twcury + twfh;
  twypos ++;
  var remtxt;
  remtxt := chracc - twxpos + 1;
  twcurx := txtx;
  twxpos := 0;
  twcl := twcl + 1;
  if(txtinput == 13)
  twtxtc := twtxtcount;
  twtxtcount := 0;
  endif
  for(n := 0; n < remtxt; n ++)
  txtbuf[(chracc * (twypos - 1)) + (chracc - n)] := 0;
  next
  endif

  if(txtinput == 8)
  if(twypos < 1 && twxpos < 1)
  return;
  endif
  var lenct; lenct := twtxtcount;
  if((twcurx - txtx + 6) < (10) && lenct > 0 && twcury > twfh)
  skip2 := 1;
  twcury := twcury - twfh;
  twypos --;
  twcurx := txtx + (((txtw / twfw) * twfw) - twfw);
  twxpos := chracc - 1;
  drawChar2tw(twcurx, twcury, 32, twcolnum, txtb, twfont);
  txtbuf[(chracc * twypos) + twxpos] := txtinput;
  //txfcol[(chracc * twypos) + twxpos] := twcolnum;
  endif
  if(twcurx > txtx && lenct > 0  && skip2 == 0)
  twcurx := twcurx - twfw;
  twxpos --;
  drawChar2tw(twcurx, twcury, 32, twcolnum, txtb, twfont);
  txtbuf[(chracc * twypos) + twxpos] := txtinput;
  //txfcol[(chracc * twypos) + twxpos] := twcolnum;
  endif
  if(twtxtcount > 0)
  twtext[twtxtcount] := 0; twtxtcount --;
  endif
  endif

  if((twcury - txty) + twfh > txth)
  gfx_ScreenCopyPaste(txtx, txty + twfh, txtx, txty, txtw, (chrdwn - 1) * twfh);
  twcury := twcury - twfh;
  twypos --;
  gfx_RectangleFilled(twcurx, twcury, twcurx + (txtw - 1) - 1, twcury + twfh, txtb);
  endif

  drawChar2tw(twcurx, twcury, 95, txtf, txtb, twfont);

  endfunc

  func TextWindow(var frame, var x, var y, var w, var h, var font, var txtcolor, var txbcolor, var frcolor)
  //TextOpacity(true);
  txt_FontID(font);
  twfw := charwidth('W');
  twfh := charheight('W') + 1;
  if(w < 24) w := 24;
  if(h < 31) h := 31;
  if(x < 0) x := 0;
  if(y < 0) y := 0;
  if((w + x) > width) w := w - ((w + x) - width);
  if((h + y) > height) h := h - ((h + y) - height);
  twxpos := 0;
  twypos := 0;
  txtwin := 1;
  //TWtextcolor(txtcolor);
  txtf := txtcolor;
  txtb := txbcolor;
  txtx := x + 6;
  twcurx := txtx;
  txty := y + 6;
  twcury := txty;
  txtw := w - 8;
  txth := h - 8;
  twtxtcount := 0;
  twframe := 1;
  twframecol := frcolor;
  if(frame == 1)
  gfx_Panel(0, x, y, w, h, frcolor);
  gfx_RectangleFilled(x + 3, y + 3, (x + 3) + (w - 6) - 1, (y + 3) + (h - 6) - 1, txbcolor);
  endif

  endfunc

  func drawChar2tw(var tx, var ty, var tc, var tf, var tb, var ts)

  if((tx >= width)||(ty >= height)||((tx + (8 + 1) * ts - 1) < 0)||((ty + 16 * ts - 1) < 0))
  return;
  endif
  if(tc < 32 || tc > 128)
  return;
  endif
  txt_FontID(ts);
  txt_FGcolour(tf);
  //TWtextcolor(tf);
  txt_BGcolour(tb);
  txt_Width(1);
  txt_Height(1);
  gfx_MoveTo(tx, ty);
  if(tc > 32)
  putch(tc);
  else
  gfx_RectangleFilled(tx, ty, tx + twfw, ty + twfh, tb);
  endif

  endfunc

  func TWtextcolor(var twc)
  txtf := twc;

  endfunc

  func TextWindowRestore()

  var n;
  var o;
  var chracc;
  chracc := txtw / (twfw);
  var chrdwn;
  chrdwn := txth / twfh;
  txtwin := 1;
  twtext[0] := 0;
  var tcoltw;
  if(twframe)
  gfx_Panel(twframe, txtx - 6, txty - 6, txtw + 8 , txth + 8, twframecol);
  gfx_RectangleFilled(txtx - 3, txty - 3, (txtx - 3) + (txtw + 2) - 1, (txty - 3) + (txth + 2) - 1, txtb);
  else
  gfx_RectangleFilled(txtx - 3, txty - 3, (txtx - 3) + (txtw + 2) - 1, (txty - 3) + (txth + 2) - 1, txtb);
  endif
  var tempc;
  for(n := 0; n < (chrdwn - 1); n ++)
  for(o := 0; o < chracc; o ++)
  tempc := txtbuf[(n * chracc) + o];
  txtbuf[((n * chracc) +o)] := tempc;
  if(tempc < 32)
  tempc := 32;
  endif
  tcoltw := txfcol[(n  * chracc) + o];
  drawChar2tw(txtx + ((twfw) * o), txty + (twfh * n), tempc, tcoltw, txtb, twfont);
  next
  next
  drawChar2tw(twcurx, twcury, 95, txtf, txtb, twfont);
  endfunc

  func GetCommand()

    var cs;
    to(CMDstring);
    if(twtxtc > 0)
    for(cs := 0; cs < twtxtc ; cs ++)
    putch(twtext[cs]);
    to(APPEND);
    next
    endif
    //putch(twtext[twtxtc]);
    //to(APPEND);
    if(CR)putch(13);
    if(CR)to(APPEND);
    if(NL)
    putch(10);
    else
    putch(0);
    endif
    //endif
    return twtxtc;
  endfunc

func TWMoveTo(var twcrx, var twcry)
  if(twcrx <= chracc && twcry <= chrdwn && chracc > 0 && chrdwn > 0)
  twcurx := txtx + (twfw * twcrx);
  twcury := txty + (twfh * twcry);
  twxpos := twcrx;
  twypos := twcry;
  return true;
  else
  return false;
  endif
endfunc
