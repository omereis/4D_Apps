//
// Added 21/08/2018 08:42:12
//
// Use 'ImageTouched' to detect 'current' object compare to values such as iWinbutton0
// to determine the object for which touch has just been released.
//

var count;

if (ImageTouched == iLeddigits0)
    ImageTouched := -1;
    WriteObject(tUserled, 0, 0);

    count++;
    if (count > 50) count := 0;
    WriteObject(tLeddigits, 0, count);
endif
