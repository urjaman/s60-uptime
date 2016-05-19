#include <e32std.h>
#include <e32hal.h>
#include <aknglobalnote.h>
#include <aknapp.h>

EXPORT_C CApaApplication* NewApplication() {
    {
        TTimeIntervalMicroSeconds32 period;
        UserHal::TickPeriod(period);
        TUint hz = 1000000UL / period.Int();
        TUint uptimesec = User::TickCount() / hz;
        TUint days = uptimesec / (24*60*60);
        uptimesec %= (24*60*60);
        TUint hours = uptimesec / (60*60);
        uptimesec %= (60*60);
        TUint mins = uptimesec / 60;
        uptimesec %= 60;
        CAknGlobalNote* globalNote = CAknGlobalNote::NewLC();
        TBuf<256> aDes;
        aDes.Format(_L("%ud %02u:%02u:%02u\nHZ: %u"), days, hours, mins, uptimesec, hz);
        globalNote->ShowNoteL(EAknGlobalInformationNote, aDes);
        CleanupStack::PopAndDestroy(globalNote);
    }
    User::Exit(0);
    return 0;
}

GLDEF_C TInt E32Dll( TDllReason /*aReason*/ ) {
    return KErrNone;
}
