// -*- mode:c++; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2 -*-
/*
 *  Copyright 2010 ZXing authors All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <zxing/ZXing.h>
#include <zxing/MultiFormatReader.h>
#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/ReaderException.h>

using zxing::Ref;
using zxing::Result;
using zxing::MultiFormatReader;

// VC++
using zxing::DecodeHints;
using zxing::BinaryBitmap;

MultiFormatReader::MultiFormatReader() {}
  
Ref<Result> MultiFormatReader::decode(Ref<BinaryBitmap> image) {
  setHints(DecodeHints::DEFAULT_HINT);
  return decodeInternal(image);
}

Ref<Result> MultiFormatReader::decode(Ref<BinaryBitmap> image, DecodeHints hints) {
  setHints(hints);
  return decodeInternal(image);
}

Ref<Result> MultiFormatReader::decodeWithState(Ref<BinaryBitmap> image) {
  // Make sure to set up the default state so we don't crash
  if (readers_.size() == 0) {
    setHints(DecodeHints::DEFAULT_HINT);
  }
  return decodeInternal(image);
}

void MultiFormatReader::setHints(DecodeHints hints) {
  hints_ = hints;
  readers_.clear();

  if (hints.containsFormat(BarcodeFormat::QR_CODE)) {
    readers_.push_back(Ref<Reader>(new zxing::qrcode::QRCodeReader()));
  }
  /*
  if (hints.contains(BarcodeFormat.MAXICODE)) {
    readers.add(new MaxiCodeReader());
  }
  */

}

Ref<Result> MultiFormatReader::decodeInternal(Ref<BinaryBitmap> image) {
  for (unsigned int i = 0; i < readers_.size(); i++) {
    try {
      return readers_[i]->decode(image, hints_);
    } catch (ReaderException const& re) {
      (void)re;
      // continue
    }
  }
  throw ReaderException("No code detected");
}
  
MultiFormatReader::~MultiFormatReader() {}
