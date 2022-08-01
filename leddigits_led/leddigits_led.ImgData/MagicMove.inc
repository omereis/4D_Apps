//
// Added 21/08/2018 08:42:12
//
// Use 'ImageTouched' to detect 'current' object compare to values such as iWinbutton0
// to determine the object for which a touch move has just been detected.
//


if (ImageTouched == iLeddigits0)
    ImageTouched := -1;
endif
