#!/usr/bin/python

# Lists information on installed package listed on command line.

# Usage:

# python rpminfo.py package_name

import rpm, sys

def printEntry(header, label, format, extra):

    value = header.sprintf(format).strip()

    print ("%-20s: %s %s" % (label, value, extra))

def printHeader(h):

    if h[rpm.RPMTAG_SOURCEPACKAGE]:

        extra = " source package"

    else:

        extra = " binary package"

    printEntry(h, 'Package', "%{NAME}-%{VERSION}-%{RELEASE}", extra)

    printEntry(h, 'Group', "%{GROUP}", '')

    printEntry(h, 'Summary', "%{Summary}", '')

    printEntry(h, 'Arch-OS-Platform', "%{ARCH}-%{OS}-%{PLATFORM}", '')

    printEntry(h, 'Vendor', "%{Vendor}", '')

    printEntry(h, 'URL', "%{URL}", '')

    printEntry(h, 'Size', "%{Size}", '')

    printEntry(h, 'Installed on', "%{INSTALLTID:date}", '')

    print (h['description'])

    print ("Files:")

    fi = h.fiFromHeader()
    print (fi)
    for item in fi:
        print (item[0])

    # Dependencies

    print ("Provides:")
    print (h.dsFromHeader('providename'))
    for item in h.dsFromHeader('providename'):
        print (item[0])

    print ("Requires:")
    print (h.dsFromHeader('requirename'))
    for item in h.dsFromHeader('requirename'):
        print (item[0])

    if h.dsFromHeader('obsoletename'):
        print ("Obsoletes:")
        print (h.dsFromHeader('obsoletename'))
        for item in h.dsFromHeader('obsoletename'):
            print (item[0])

    if h.dsFromHeader('conflictname'):
        print ("Conflicts:")
        print (h.dsFromHeader('conflictname'))
        for item in h.dsFromHeader('conflictname'):
            print (item[0])

ts = rpm.TransactionSet()
print (dir(ts))
mi = ts.dbMatch( 'name', sys.argv[1] )

for h in mi:

    printHeader(h)
