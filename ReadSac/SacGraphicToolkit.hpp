//
// Created by cypress on 03/03/2018.
//

#ifndef SACTOOLKIT_SACGRAPHICTOOLKIT_HPP
#define SACTOOLKIT_SACGRAPHICTOOLKIT_HPP

#include <QtWidgets/QApplication>
#include <QtCore/qmath.h>
#include <QtCore/QVector>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_legend.h>
#include <qwt_point_data.h>
#include <complex>

using namespace std;

class SacGraphicToolkit {
public:
    enum FFTPlotType {
        amp = 0;
        phase = 1;
    };

    void PlotFFT(complex<float> *, FFTPlotType);

    SacGraphicToolkit() = delete;
    ~SacGraphicToolkit() = delete;
};


#endif //SACTOOLKIT_SACGRAPHICTOOLKIT_HPP
