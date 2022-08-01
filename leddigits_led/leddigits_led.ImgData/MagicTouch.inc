//
// Added 21/08/2018 08:38:59
//
// Use 'ImageTouched' to detect 'current' object compare to values such as iWinbutton0
// to determine the object for which a touch has just been detected.
//

if (ImageTouched == iLeddigits0)
    ImageTouched := -1;
    WriteObject(tUserled, 0, 1);
endif
