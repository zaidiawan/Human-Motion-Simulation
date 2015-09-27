#ifndef ENUMERATIONS_H
#define ENUMERATIONS_H

enum AngleUnits_T {
    radians,
    degrees
};
enum PeriodMode_T {
    time,
    percent
};
enum InterpolType_T {
    cubic,
    akima,
    Constantini,
    CFourier
};
enum MarkersStatus_T {
    MarkersInserted ,
    MarkersMoved,
    MarkersUnchanged

};

enum ScalingReason_T {
    MoreSpace ,
    PeriodModeChanged,
    AngleUnitsChanged
};

enum MarkerPosStatus_T {
    Same ,
    Different
};

enum MarkersObjType_T {
    HipMarkers ,
    KneeMarkers
};
enum CurveStatus_T {
    ShowDelayed ,
    ShowWithoutDelay
};









#endif // ENUMERATIONS_H
