//
//  SBSSymbologySettings.h
//  BarcodeScanner
//
//  Created by Moritz Hartmeier on 20/05/15.
//  Copyright (c) 2015 Scandit AG. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SBSCode.h"


extern NSString *const SBSSymbologySettingsExtensionRemoveLeadingZero;
extern NSString *const SBSSymbologySettingsExtensionTiny;


/* Possible checksum algorithms. */
typedef enum {
    SBSChecksumNone = 0x00,
    SBSChecksumMod10 = 0x01,
    SBSChecksumMod11 = 0x02,
    SBSChecksumMod47 = 0x04,
    SBSChecksumMod103 = 0x10,
    SBSChecksumMod1010 = 0x20,
    SBSChecksumMod1110 = 0x40,
} SBSChecksum;


/**
 * Symbology specific settings.
 */
@interface SBSSymbologySettings : NSObject

/* The symbology these settings belong to. */
@property (nonatomic, assign, readonly) SBSSymbology symbology;

/**
 * \brief Whether decoding of this symbology is enabled.
 *
 * This property only enables/disables decoding of dark codes on bright background. If color-
 * inverted (bright on dark) codes for this symbology are required, enable them through the 
 * colorInvertedEnabled property. By default decoding of all symbologies is disabled.
 *
 * It is advised to only enable symbologies that are required by the application as every enabled 
 * symbology adds processing overhead.
 *
 * \since 4.7.0
 */
@property (nonatomic, assign) BOOL enabled;

/**
 * \brief Whether color-inverted decoding of this symbology is enabled.
 *
 * This property only enables/disables decoding of bright codes on dark background. By default 
 * color-inverted decoding of all symbologies is disabled.
 *
 * It is advised to only enable symbologies that are required by the application as every enabled 
 * symbology adds processing overhead.
 *
 * \since 4.7.0
 */
@property (nonatomic, assign) BOOL colorInvertedEnabled;

/**
 * \brief Active optional checksums for this symbology.
 *
 * This property contains the additional checksums for this symbology. When a barcode has been 
 * decoded, the checksums contained are evaluated in addition to any mandatory checksum defined by
 * the symbology specification. If any of the checksums matches, the code is returned as
 * recognized, otherwise it is discarded.
 *
 * \since 4.7.0
 */
@property (nonatomic, strong) NSSet *checksums;

/**
 * \brief This function allows to control the length of barcodes to be decoded.
 *
 * Call this function to enable decoding of long codes which can not be decoded with the default
 * settings, or to optimize decoder performance for codes of certain lengths. This is useful when
 * it is known that the application only requires scanning of particular barcode lengths.
 *
 * The mapping from characters to symbols is symbology-specific. For some symbologies, the start
 * and end characters are included, others include checksums characters in the symbol counts.
 *
 * The active symbol count setting is ignored for fixed-size barcodes (the EAN and UPC family of
 * codes) as well as 2d codes. For other symbologies, see <a href="../c_api/symbologies.html">
 * Calculating symbol counts for variable-length symbologies</a>.
 *
 * \since 4.7.0
 */
@property (nonatomic, strong) NSSet *activeSymbolCounts;

/**
 * \brief Determine whether a certain extension is enabled for the symbology.
 *
 * Extensions are custom features that are only supported by a small number of
 * symbologies. For a list of supported extensions, consult the constants of this class.
 *
 * \param extension Name of the extension.
 *
 * \return YES if the extension is enabled, NO if not.
 *
 * \since 4.7.0
 */
- (BOOL)isExtensionEnabled:(NSString *)extension;

/**
 * \brief Activate/Deactivate a custom extension for the symbology.
 *
 * Extensions are custom features that are only supported by a small number of
 * symbologies. For a list of supported extensions, consult the constants of this class.
 *
 * \param extension Name of the extension.
 * \param enabled Whether the extension should be enabled/disabled.
 *
 *
 * \since 4.7.0
 */
- (void)setExtension:(NSString *)extension enabled:(BOOL)enabled;

@end
