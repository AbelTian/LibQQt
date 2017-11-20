QT       += core gui

#lessThan(QT_MAJOR_VERSION, 5): QT += declarative
greaterThan(QT_MAJOR_VERSION, 4): QT += quick

DEFINES += QZXING_LIBRARY \
        ZXING_ICONV_CONST \
        DISABLE_LIBRARY_FEATURES

greaterThan(QT_MAJOR_VERSION, 4) {
    HEADERS += $$PWD/imagehandler.h
    SOURCES += $$PWD/imagehandler.cpp
}

HEADERS += $$PWD/QZXing_global.h \
    $$PWD/CameraImageWrapper.h \
    $$PWD/QZXing.h \
    $$PWD/zxing/zxing/ZXing.h \
    $$PWD/zxing/zxing/IllegalStateException.h \
    $$PWD/zxing/zxing/InvertedLuminanceSource.h \
    $$PWD/zxing/zxing/ChecksumException.h \
    $$PWD/zxing/zxing/ResultPointCallback.h \
    $$PWD/zxing/zxing/ResultPoint.h \
    $$PWD/zxing/zxing/Result.h \
    $$PWD/zxing/zxing/ReaderException.h \
    $$PWD/zxing/zxing/Reader.h \
    $$PWD/zxing/zxing/NotFoundException.h \
    $$PWD/zxing/zxing/MultiFormatReader.h \
    $$PWD/zxing/zxing/LuminanceSource.h \
    $$PWD/zxing/zxing/FormatException.h \
    $$PWD/zxing/zxing/Exception.h \
    $$PWD/zxing/zxing/DecodeHints.h \
    $$PWD/zxing/zxing/BinaryBitmap.h \
    $$PWD/zxing/zxing/Binarizer.h \
    $$PWD/zxing/zxing/BarcodeFormat.h \
    $$PWD/zxing/zxing/common/StringUtils.h \
    $$PWD/zxing/zxing/common/Str.h \
    $$PWD/zxing/zxing/common/Point.h \
    $$PWD/zxing/zxing/common/PerspectiveTransform.h \
    $$PWD/zxing/zxing/common/IllegalArgumentException.h \
    $$PWD/zxing/zxing/common/HybridBinarizer.h \
    $$PWD/zxing/zxing/common/GridSampler.h \
    $$PWD/zxing/zxing/common/GreyscaleRotatedLuminanceSource.h \
    $$PWD/zxing/zxing/common/GreyscaleLuminanceSource.h \
    $$PWD/zxing/zxing/common/GlobalHistogramBinarizer.h \
    $$PWD/zxing/zxing/common/DetectorResult.h \
    $$PWD/zxing/zxing/common/DecoderResult.h \
    $$PWD/zxing/zxing/common/Counted.h \
    $$PWD/zxing/zxing/common/CharacterSetECI.h \
    $$PWD/zxing/zxing/common/BitSource.h \
    $$PWD/zxing/zxing/common/BitMatrix.h \
    $$PWD/zxing/zxing/common/BitArray.h \
    $$PWD/zxing/zxing/common/Array.h \
    $$PWD/zxing/zxing/common/detector/MathUtils.h \
    $$PWD/zxing/zxing/common/detector/JavaMath.h \
    $$PWD/zxing/zxing/common/detector/WhiteRectangleDetector.h \
    $$PWD/zxing/zxing/common/detector/MonochromeRectangleDetector.h \
    $$PWD/zxing/zxing/common/reedsolomon/ReedSolomonException.h \
    $$PWD/zxing/zxing/common/reedsolomon/ReedSolomonDecoder.h \
    $$PWD/zxing/zxing/common/reedsolomon/GenericGFPoly.h \
    $$PWD/zxing/zxing/common/reedsolomon/GenericGF.h \
    $$PWD/zxing/zxing/qrcode/Version.h \
    $$PWD/zxing/zxing/qrcode/QRCodeReader.h \
    $$PWD/zxing/zxing/qrcode/FormatInformation.h \
    $$PWD/zxing/zxing/qrcode/ErrorCorrectionLevel.h \
    $$PWD/zxing/zxing/qrcode/decoder/Mode.h \
    $$PWD/zxing/zxing/qrcode/decoder/Decoder.h \
    $$PWD/zxing/zxing/qrcode/decoder/DecodedBitStreamParser.h \
    $$PWD/zxing/zxing/qrcode/decoder/DataMask.h \
    $$PWD/zxing/zxing/qrcode/decoder/DataBlock.h \
    $$PWD/zxing/zxing/qrcode/decoder/BitMatrixParser.h \
    $$PWD/zxing/zxing/qrcode/detector/FinderPatternInfo.h \
    $$PWD/zxing/zxing/qrcode/detector/FinderPatternFinder.h \
    $$PWD/zxing/zxing/qrcode/detector/FinderPattern.h \
    $$PWD/zxing/zxing/qrcode/detector/Detector.h \
    $$PWD/zxing/zxing/qrcode/detector/AlignmentPatternFinder.h \
    $$PWD/zxing/zxing/qrcode/detector/AlignmentPattern.h \
    $$PWD/zxing/zxing/multi/MultipleBarcodeReader.h \
    $$PWD/zxing/zxing/multi/GenericMultipleBarcodeReader.h \
    $$PWD/zxing/zxing/multi/ByQuadrantReader.h \
    $$PWD/zxing/zxing/multi/qrcode/QRCodeMultiReader.h \
    $$PWD/zxing/zxing/multi/qrcode/detector/MultiFinderPatternFinder.h \
    $$PWD/zxing/zxing/multi/qrcode/detector/MultiDetector.h \
    $$PWD/zxing/bigint/NumberlikeArray.hh \
    $$PWD/zxing/bigint/BigUnsignedInABase.hh \
    $$PWD/zxing/bigint/BigUnsigned.hh \
    $$PWD/zxing/bigint/BigIntegerUtils.hh \
    $$PWD/zxing/bigint/BigIntegerLibrary.hh \
    $$PWD/zxing/bigint/BigIntegerAlgorithms.hh \
    $$PWD/zxing/bigint/BigInteger.hh

SOURCES += $$PWD/CameraImageWrapper.cpp \
    $$PWD/qzxing.cpp \
    $$PWD/zxing/zxing/ResultIO.cpp \
    $$PWD/zxing/zxing/InvertedLuminanceSource.cpp \
    $$PWD/zxing/zxing/ChecksumException.cpp \
    $$PWD/zxing/zxing/ResultPointCallback.cpp \
    $$PWD/zxing/zxing/ResultPoint.cpp \
    $$PWD/zxing/zxing/Result.cpp \
    $$PWD/zxing/zxing/Reader.cpp \
    $$PWD/zxing/zxing/MultiFormatReader.cpp \
    $$PWD/zxing/zxing/LuminanceSource.cpp \
    $$PWD/zxing/zxing/FormatException.cpp \
    $$PWD/zxing/zxing/Exception.cpp \
    $$PWD/zxing/zxing/DecodeHints.cpp \
    $$PWD/zxing/zxing/BinaryBitmap.cpp \
    $$PWD/zxing/zxing/Binarizer.cpp \
    $$PWD/zxing/zxing/BarcodeFormat.cpp \
    $$PWD/zxing/zxing/common/StringUtils.cpp \
    $$PWD/zxing/zxing/common/Str.cpp \
    $$PWD/zxing/zxing/common/PerspectiveTransform.cpp \
    $$PWD/zxing/zxing/common/IllegalArgumentException.cpp \
    $$PWD/zxing/zxing/common/HybridBinarizer.cpp \
    $$PWD/zxing/zxing/common/GridSampler.cpp \
    $$PWD/zxing/zxing/common/GreyscaleRotatedLuminanceSource.cpp \
    $$PWD/zxing/zxing/common/GreyscaleLuminanceSource.cpp \
    $$PWD/zxing/zxing/common/GlobalHistogramBinarizer.cpp \
    $$PWD/zxing/zxing/common/DetectorResult.cpp \
    $$PWD/zxing/zxing/common/DecoderResult.cpp \
    $$PWD/zxing/zxing/common/CharacterSetECI.cpp \
    $$PWD/zxing/zxing/common/BitSource.cpp \
    $$PWD/zxing/zxing/common/BitMatrix.cpp \
    $$PWD/zxing/zxing/common/BitArray.cpp \
    $$PWD/zxing/zxing/common/BitArrayIO.cpp \
    $$PWD/zxing/zxing/common/detector/WhiteRectangleDetector.cpp \
    $$PWD/zxing/zxing/common/detector/MonochromeRectangleDetector.cpp \
    $$PWD/zxing/zxing/common/reedsolomon/ReedSolomonException.cpp \
    $$PWD/zxing/zxing/common/reedsolomon/ReedSolomonDecoder.cpp \
    $$PWD/zxing/zxing/common/reedsolomon/GenericGFPoly.cpp \
    $$PWD/zxing/zxing/common/reedsolomon/GenericGF.cpp \
    $$PWD/zxing/zxing/qrcode/QRCodeReader.cpp \
    $$PWD/zxing/zxing/multi/MultipleBarcodeReader.cpp \
    $$PWD/zxing/zxing/multi/GenericMultipleBarcodeReader.cpp \
    $$PWD/zxing/zxing/multi/ByQuadrantReader.cpp \
    $$PWD/zxing/zxing/multi/qrcode/QRCodeMultiReader.cpp \
    $$PWD/zxing/zxing/multi/qrcode/detector/MultiFinderPatternFinder.cpp \
    $$PWD/zxing/zxing/multi/qrcode/detector/MultiDetector.cpp \
    $$PWD/zxing/zxing/qrcode/decoder/QRBitMatrixParser.cpp \
    $$PWD/zxing/zxing/qrcode/decoder/QRDataBlock.cpp \
    $$PWD/zxing/zxing/qrcode/decoder/QRDataMask.cpp \
    $$PWD/zxing/zxing/qrcode/decoder/QRDecodedBitStreamParser.cpp \
    $$PWD/zxing/zxing/qrcode/decoder/QRDecoder.cpp \
    $$PWD/zxing/zxing/qrcode/decoder/QRMode.cpp \
    $$PWD/zxing/zxing/qrcode/detector/QRAlignmentPattern.cpp \
    $$PWD/zxing/zxing/qrcode/detector/QRAlignmentPatternFinder.cpp \
    $$PWD/zxing/zxing/qrcode/detector/QRDetector.cpp \
    $$PWD/zxing/zxing/qrcode/detector/QRFinderPattern.cpp \
    $$PWD/zxing/zxing/qrcode/detector/QRFinderPatternFinder.cpp \
    $$PWD/zxing/zxing/qrcode/detector/QRFinderPatternInfo.cpp \
    $$PWD/zxing/zxing/qrcode/QRVersion.cpp \
    $$PWD/zxing/zxing/qrcode/QRFormatInformation.cpp \
    $$PWD/zxing/zxing/qrcode/QRErrorCorrectionLevel.cpp \
    $$PWD/zxing/bigint/BigUnsignedInABase.cc \
    $$PWD/zxing/bigint/BigUnsigned.cc \
    $$PWD/zxing/bigint/BigIntegerUtils.cc \
    $$PWD/zxing/bigint/BigIntegerAlgorithms.cc \
    $$PWD/zxing/bigint/BigInteger.cc

win32-msvc*{
    HEADERS += $$PWD/zxing/win32/zxing/iconv.h \
                $$PWD/zxing/win32/zxing/msvc/stdint.h
    SOURCES += $$PWD/zxing/win32/zxing/win_iconv.c
}

win32-g++{
    HEADERS += $$PWD/zxing/win32/zxing/iconv.h
    SOURCES += $$PWD/zxing/win32/zxing/win_iconv.c
}
