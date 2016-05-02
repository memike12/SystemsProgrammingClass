#!/bin/bash

red='\e[0;31m'
green='\e[0;32m'
nc='\e[0m'        

test_bash(){
    echo "--- Test Bash ---"
    cd bash
    
    echo -n -e "#> ./allnumbers.sh a \t\t\t\t\t"
    res="$(./allnumbers.sh a)"
    if [ "$res" == ""  ];
    then
	echo -e "$green pass $nc"
    else
	echo -e "$red FAIL $nc"
    fi


    echo -n -e "#> ./allnumbers.sh 1 2 \t\t\t\t\t"
    res=$(./allnumbers.sh 1 2 |  tr '\n' ' ')
    if [ "$res" == "1 2 " ];
    then
	echo -e "$green pass $nc"
    else
	echo -e "$red FAIL $nc"
    fi

    echo -n -e "#> ./allnumbers.sh 1 a 2 3 b 4\t\t\t\t"
    res=$(./allnumbers.sh 1 a 2 3 b 4 | tr '\n' ' ')
    if [ "$res" == "1 2 3 4 " ];
    then
	echo -e "$green pass $nc"
    else
	echo -e "$red FAIL $nc : '$res'"
    fi

    cd ..
}

test_cprog(){
    echo "--- Test C-Prog ---"
    cd c-prog

    echo -n -e "#> ./wordcounter sample.txt\t\t\t\t"
    res="$(./wordcounter sample.txt | tr '\n' ' ')"
    expect="---- sample.txt ---- 0: the 3 1: large 5 2: brown 5 3: fox 3 4: jumped 6 5: over 4 6: the 3 7: lazy 4 8: dog 3  "
    if [ "$res" == "$expect"  ];
    then
	echo -e "$green pass $nc"
    else
	echo -e "$red FAIL $nc"
    fi

    echo -n -e "#> ./wordcounter hemmingway.txt\t\t\t\t"
    res="$(./wordcounter hemmingway.txt | tr '\n' ' ')"
    expect="---- hemmingway.txt ---- 0: One 3 1: hot 3 2: evening 7 3: in 2 4: Padua 5 5: they 4 6: carried 7 7: him 3 8: up 2 9: onto 4 10: the 3 11: roof 4 12: and 3 13: he 2 14: could 5 15: look 4 16: out 3 17: over 4 18: the 3 19: top 3 20: of 2 21: the 3 22: town. 5 23: There 5 24: were 4 25: chimney 7 26: swifts 6 27: in 2 28: the 3 29: sky. 4 30: After 5 31: a 1 32: while 5 33: it 2 34: got 3 35: dark 4 36: and 3 37: the 3 38: searchlights 12 39: came 4 40: out. 4 41: The 3 42: others 6 43: went 4 44: down 4 45: and 3 46: took 4 47: the 3 48: bottles 7 49: with 4 50: them. 5 51: He 2 52: and 3 53: Luz 3 54: could 5 55: hear 4 56: them 4 57: below 5 58: on 2 59: the 3 60: balcony. 8 61: Luz 3 62: sat 3 63: on 2 64: the 3 65: bed. 4 66: She 3 67: was 3 68: cool 4 69: and 3 70: fresh 5 71: in 2 72: the 3 73: hot 3 74: night. 6 75: Luz 3 76: stayed 6 77: on 2 78: night 5 79: duty 4 80: for 3 81: three 5 82: months. 7 83: They 4 84: were 4 85: glad 4 86: to 2 87: let 3 88: her. 4 89: When 4 90: they 4 91: operated 8 92: on 2 93: him 3 94: she 3 95: prepared 8 96: him 3 97: for 3 98: the 3 99: operating 9 100: table; 6 101: and 3 102: they 4 103: had 3 104: a 1 105: joke 4 106: about 5 107: friend 6 108: or 2 109: enema. 6 110: He 2 111: went 4 112: under 5 113: the 3 114: anaesthetic 11 115: holding 7 116: tight 5 117: on 2 118: to 2 119: himself 7 120: so 2 121: he 2 122: would 5 123: not 3 124: blab 4 125: about 5 126: anything 8 127: during 6 128: the 3 129: silly, 6 130: talky 5 131: time. 5 132: After 5 133: he 2 134: got 3 135: on 2 136: crutches 8 137: he 2 138: used 4 139: to 2 140: take 4 141: the 3 142: temperatures 12 143: so 2 144: Luz 3 145: would 5 146: not 3 147: have 4 148: to 2 149: get 3 150: up 2 151: from 4 152: the 3 153: bed. 4 154: There 5 155: were 4 156: only 4 157: a 1 158: few 3 159: patients, 9 160: and 3 161: they 4 162: all 3 163: knew 4 164: about 5 165: it. 3 166: They 4 167: all 3 168: liked 5 169: Luz. 4 170: As 2 171: he 2 172: walked 6 173: back 4 174: along 5 175: the 3 176: halls 5 177: he 2 178: thought 7 179: of 2 180: Luz 3 181: in 2 182: his 3 183: bed. 4 184: Before 6 185: he 2 186: went 4 187: back 4 188: to 2 189: the 3 190: front 5 191: they 4 192: went 4 193: into 4 194: the 3 195: Duomo 5 196: and 3 197: prayed. 7 198: It 2 199: was 3 200: dim 3 201: and 3 202: quiet, 6 203: and 3 204: there 5 205: were 4 206: other 5 207: people 6 208: praying. 8 209: They 4 210: wanted 6 211: to 2 212: get 3 213: married, 8 214: but 3 215: there 5 216: was 3 217: not 3 218: enough 6 219: time 4 220: for 3 221: the 3 222: banns, 6 223: and 3 224: neither 7 225: of 2 226: them 4 227: had 3 228: birth 5 229: certificates. 13 230: They 4 231: felt 4 232: as 2 233: though 6 234: they 4 235: were 4 236: married, 8 237: but 3 238: they 4 239: wanted 6 240: everyone 8 241: to 2 242: know 4 243: about 5 244: it, 3 245: and 3 246: to 2 247: make 4 248: it 2 249: so 2 250: they 4 251: could 5 252: not 3 253: lose 4 254: it. 3 255: Luz 3 256: wrote 5 257: him 3 258: many 4 259: letters 7 260: that 4 261: he 2 262: never 5 263: got 3 264: until 5 265: after 5 266: the 3 267: armistice. 10 268: Fifteen 7 269: came 4 270: in 2 271: a 1 272: bunch 5 273: to 2 274: the 3 275: front 5 276: and 3 277: he 2 278: sorted 6 279: them 4 280: by 2 281: the 3 282: dates 5 283: and 3 284: read 4 285: them 4 286: all 3 287: straight 8 288: through. 8 289: They 4 290: were 4 291: all 3 292: about 5 293: the 3 294: hospital, 9 295: and 3 296: how 3 297: much 4 298: she 3 299: loved 5 300: him 3 301: and 3 302: how 3 303: it 2 304: was 3 305: impossible 10 306: to 2 307: get 3 308: along 5 309: without 7 310: him 3 311: and 3 312: how 3 313: terrible 8 314: it 2 315: was 3 316: missing 7 317: him 3 318: at 2 319: night. 6 320: After 5 321: the 3 322: armistice 9 323: they 4 324: agreed 6 325: he 2 326: should 6 327: go 2 328: home 4 329: to 2 330: get 3 331: a 1 332: job 3 333: so 2 334: they 4 335: might 5 336: be 2 337: married. 8 338: Luz 3 339: would 5 340: not 3 341: come 4 342: home 4 343: until 5 344: he 2 345: had 3 346: a 1 347: good 4 348: job 3 349: and 3 350: could 5 351: come 4 352: to 2 353: New 3 354: York 4 355: to 2 356: meet 4 357: her. 4 358: It 2 359: was 3 360: understood 10 361: he 2 362: would 5 363: not 3 364: drink, 6 365: and 3 366: he 2 367: did 3 368: not 3 369: want 4 370: to 2 371: see 3 372: his 3 373: friends 7 374: or 2 375: anyone 6 376: in 2 377: the 3 378: States. 7 379: Only 4 380: to 2 381: get 3 382: a 1 383: job 3 384: and 3 385: be 2 386: married. 8 387: On 2 388: the 3 389: train 5 390: from 4 391: Padua 5 392: to 2 393: Milan 5 394: they 4 395: quarreled 9 396: about 5 397: her 3 398: not 3 399: being 5 400: willing 7 401: to 2 402: come 4 403: home 4 404: at 2 405: once. 5 406: When 4 407: they 4 408: had 3 409: to 2 410: say 3 411: good-bye, 9 412: in 2 413: the 3 414: station 7 415: at 2 416: Milan, 6 417: they 4 418: kissed 6 419: good-bye, 9 420: but 3 421: were 4 422: not 3 423: finished 8 424: with 4 425: the 3 426: quarrel. 8 427: He 2 428: felt 4 429: sick 4 430: about 5 431: saying 6 432: good-bye 8 433: like 4 434: that. 5 435: He 2 436: went 4 437: to 2 438: America 7 439: on 2 440: a 1 441: boat 4 442: from 4 443: Genoa. 6 444: Luz 3 445: went 4 446: back 4 447: to 2 448: Pordonone 9 449: to 2 450: open 4 451: a 1 452: hospital. 9 453: It 2 454: was 3 455: lonely 6 456: and 3 457: rainy 5 458: there, 6 459: and 3 460: there 5 461: was 3 462: a 1 463: battalion 9 464: of 2 465: arditi 6 466: quartered 9 467: in 2 468: the 3 469: town. 5 470: Living 6 471: in 2 472: the 3 473: muddy, 6 474: rainy 5 475: town 4 476: in 2 477: the 3 478: winter, 7 479: the 3 480: major 5 481: of 2 482: the 3 483: battalion 9 484: made 4 485: love 4 486: to 2 487: Luz, 4 488: and 3 489: she 3 490: had 3 491: never 5 492: known 5 493: Italians 8 494: before, 7 495: and 3 496: finally 7 497: wrote 5 498: to 2 499: the 3 500: States 6 501: that 4 502: theirs 6 503: had 3 504: only 4 505: been 4 506: a 1 507: boy 3 508: and 3 509: girl 4 510: affair. 7 511: She 3 512: was 3 513: sorry, 6 514: and 3 515: she 3 516: knew 4 517: he 2 518: would 5 519: probably 8 520: not 3 521: be 2 522: able 4 523: to 2 524: understand, 11 525: but 3 526: might 5 527: some 4 528: day 3 529: forgive 7 530: her, 4 531: and 3 532: be 2 533: grateful 8 534: to 2 535: her, 4 536: and 3 537: she 3 538: expected, 9 539: absolutely 10 540: unexpectedly, 13 541: to 2 542: be 2 543: married 7 544: in 2 545: the 3 546: spring. 7 547: She 3 548: loved 5 549: him 3 550: as 2 551: always, 7 552: but 3 553: she 3 554: realized 8 555: now 3 556: it 2 557: was 3 558: only 4 559: a 1 560: boy 3 561: and 3 562: girl 4 563: love. 5 564: She 3 565: hoped 5 566: he 2 567: would 5 568: have 4 569: a 1 570: great 5 571: career, 7 572: and 3 573: believed 8 574: in 2 575: him 3 576: absolutely. 11 577: She 3 578: knew 4 579: it 2 580: was 3 581: for 3 582: the 3 583: best. 5 584: The 3 585: major 5 586: did 3 587: not 3 588: marry 5 589: her 3 590: in 2 591: the 3 592: spring, 7 593: or 2 594: any 3 595: other 5 596: time. 5 597: Luz 3 598: never 5 599: got 3 600: an 2 601: answer 6 602: to 2 603: the 3 604: letter 6 605: to 2 606: Chicago 7 607: about 5 608: it. 3 609: A 1 610: short 5 611: time 4 612: after 5 613: he 2 614: contracted 10 615: gonorrhea 9 616: from 4 617: a 1 618: sales 5 619: girl 4 620: in 2 621: a 1 622: loop 4 623: department 10 624: store 5 625: while 5 626: riding 6 627: in 2 628: a 1 629: taxicab 7 630: through 7 631: Lincoln 7 632: Park. 5  "
    if [ "$res" == "$expect"  ];
    then
	echo -e "$green pass $nc"
    else
	echo -e "$red FAIL $nc"
    fi

    echo -n -e "#> ./wordcounter hemmingway.txt sample.txt\t\t"
    res="$(./wordcounter hemmingway.txt sample.txt| tr '\n' ' ')"
    expect="---- hemmingway.txt ---- 0: One 3 1: hot 3 2: evening 7 3: in 2 4: Padua 5 5: they 4 6: carried 7 7: him 3 8: up 2 9: onto 4 10: the 3 11: roof 4 12: and 3 13: he 2 14: could 5 15: look 4 16: out 3 17: over 4 18: the 3 19: top 3 20: of 2 21: the 3 22: town. 5 23: There 5 24: were 4 25: chimney 7 26: swifts 6 27: in 2 28: the 3 29: sky. 4 30: After 5 31: a 1 32: while 5 33: it 2 34: got 3 35: dark 4 36: and 3 37: the 3 38: searchlights 12 39: came 4 40: out. 4 41: The 3 42: others 6 43: went 4 44: down 4 45: and 3 46: took 4 47: the 3 48: bottles 7 49: with 4 50: them. 5 51: He 2 52: and 3 53: Luz 3 54: could 5 55: hear 4 56: them 4 57: below 5 58: on 2 59: the 3 60: balcony. 8 61: Luz 3 62: sat 3 63: on 2 64: the 3 65: bed. 4 66: She 3 67: was 3 68: cool 4 69: and 3 70: fresh 5 71: in 2 72: the 3 73: hot 3 74: night. 6 75: Luz 3 76: stayed 6 77: on 2 78: night 5 79: duty 4 80: for 3 81: three 5 82: months. 7 83: They 4 84: were 4 85: glad 4 86: to 2 87: let 3 88: her. 4 89: When 4 90: they 4 91: operated 8 92: on 2 93: him 3 94: she 3 95: prepared 8 96: him 3 97: for 3 98: the 3 99: operating 9 100: table; 6 101: and 3 102: they 4 103: had 3 104: a 1 105: joke 4 106: about 5 107: friend 6 108: or 2 109: enema. 6 110: He 2 111: went 4 112: under 5 113: the 3 114: anaesthetic 11 115: holding 7 116: tight 5 117: on 2 118: to 2 119: himself 7 120: so 2 121: he 2 122: would 5 123: not 3 124: blab 4 125: about 5 126: anything 8 127: during 6 128: the 3 129: silly, 6 130: talky 5 131: time. 5 132: After 5 133: he 2 134: got 3 135: on 2 136: crutches 8 137: he 2 138: used 4 139: to 2 140: take 4 141: the 3 142: temperatures 12 143: so 2 144: Luz 3 145: would 5 146: not 3 147: have 4 148: to 2 149: get 3 150: up 2 151: from 4 152: the 3 153: bed. 4 154: There 5 155: were 4 156: only 4 157: a 1 158: few 3 159: patients, 9 160: and 3 161: they 4 162: all 3 163: knew 4 164: about 5 165: it. 3 166: They 4 167: all 3 168: liked 5 169: Luz. 4 170: As 2 171: he 2 172: walked 6 173: back 4 174: along 5 175: the 3 176: halls 5 177: he 2 178: thought 7 179: of 2 180: Luz 3 181: in 2 182: his 3 183: bed. 4 184: Before 6 185: he 2 186: went 4 187: back 4 188: to 2 189: the 3 190: front 5 191: they 4 192: went 4 193: into 4 194: the 3 195: Duomo 5 196: and 3 197: prayed. 7 198: It 2 199: was 3 200: dim 3 201: and 3 202: quiet, 6 203: and 3 204: there 5 205: were 4 206: other 5 207: people 6 208: praying. 8 209: They 4 210: wanted 6 211: to 2 212: get 3 213: married, 8 214: but 3 215: there 5 216: was 3 217: not 3 218: enough 6 219: time 4 220: for 3 221: the 3 222: banns, 6 223: and 3 224: neither 7 225: of 2 226: them 4 227: had 3 228: birth 5 229: certificates. 13 230: They 4 231: felt 4 232: as 2 233: though 6 234: they 4 235: were 4 236: married, 8 237: but 3 238: they 4 239: wanted 6 240: everyone 8 241: to 2 242: know 4 243: about 5 244: it, 3 245: and 3 246: to 2 247: make 4 248: it 2 249: so 2 250: they 4 251: could 5 252: not 3 253: lose 4 254: it. 3 255: Luz 3 256: wrote 5 257: him 3 258: many 4 259: letters 7 260: that 4 261: he 2 262: never 5 263: got 3 264: until 5 265: after 5 266: the 3 267: armistice. 10 268: Fifteen 7 269: came 4 270: in 2 271: a 1 272: bunch 5 273: to 2 274: the 3 275: front 5 276: and 3 277: he 2 278: sorted 6 279: them 4 280: by 2 281: the 3 282: dates 5 283: and 3 284: read 4 285: them 4 286: all 3 287: straight 8 288: through. 8 289: They 4 290: were 4 291: all 3 292: about 5 293: the 3 294: hospital, 9 295: and 3 296: how 3 297: much 4 298: she 3 299: loved 5 300: him 3 301: and 3 302: how 3 303: it 2 304: was 3 305: impossible 10 306: to 2 307: get 3 308: along 5 309: without 7 310: him 3 311: and 3 312: how 3 313: terrible 8 314: it 2 315: was 3 316: missing 7 317: him 3 318: at 2 319: night. 6 320: After 5 321: the 3 322: armistice 9 323: they 4 324: agreed 6 325: he 2 326: should 6 327: go 2 328: home 4 329: to 2 330: get 3 331: a 1 332: job 3 333: so 2 334: they 4 335: might 5 336: be 2 337: married. 8 338: Luz 3 339: would 5 340: not 3 341: come 4 342: home 4 343: until 5 344: he 2 345: had 3 346: a 1 347: good 4 348: job 3 349: and 3 350: could 5 351: come 4 352: to 2 353: New 3 354: York 4 355: to 2 356: meet 4 357: her. 4 358: It 2 359: was 3 360: understood 10 361: he 2 362: would 5 363: not 3 364: drink, 6 365: and 3 366: he 2 367: did 3 368: not 3 369: want 4 370: to 2 371: see 3 372: his 3 373: friends 7 374: or 2 375: anyone 6 376: in 2 377: the 3 378: States. 7 379: Only 4 380: to 2 381: get 3 382: a 1 383: job 3 384: and 3 385: be 2 386: married. 8 387: On 2 388: the 3 389: train 5 390: from 4 391: Padua 5 392: to 2 393: Milan 5 394: they 4 395: quarreled 9 396: about 5 397: her 3 398: not 3 399: being 5 400: willing 7 401: to 2 402: come 4 403: home 4 404: at 2 405: once. 5 406: When 4 407: they 4 408: had 3 409: to 2 410: say 3 411: good-bye, 9 412: in 2 413: the 3 414: station 7 415: at 2 416: Milan, 6 417: they 4 418: kissed 6 419: good-bye, 9 420: but 3 421: were 4 422: not 3 423: finished 8 424: with 4 425: the 3 426: quarrel. 8 427: He 2 428: felt 4 429: sick 4 430: about 5 431: saying 6 432: good-bye 8 433: like 4 434: that. 5 435: He 2 436: went 4 437: to 2 438: America 7 439: on 2 440: a 1 441: boat 4 442: from 4 443: Genoa. 6 444: Luz 3 445: went 4 446: back 4 447: to 2 448: Pordonone 9 449: to 2 450: open 4 451: a 1 452: hospital. 9 453: It 2 454: was 3 455: lonely 6 456: and 3 457: rainy 5 458: there, 6 459: and 3 460: there 5 461: was 3 462: a 1 463: battalion 9 464: of 2 465: arditi 6 466: quartered 9 467: in 2 468: the 3 469: town. 5 470: Living 6 471: in 2 472: the 3 473: muddy, 6 474: rainy 5 475: town 4 476: in 2 477: the 3 478: winter, 7 479: the 3 480: major 5 481: of 2 482: the 3 483: battalion 9 484: made 4 485: love 4 486: to 2 487: Luz, 4 488: and 3 489: she 3 490: had 3 491: never 5 492: known 5 493: Italians 8 494: before, 7 495: and 3 496: finally 7 497: wrote 5 498: to 2 499: the 3 500: States 6 501: that 4 502: theirs 6 503: had 3 504: only 4 505: been 4 506: a 1 507: boy 3 508: and 3 509: girl 4 510: affair. 7 511: She 3 512: was 3 513: sorry, 6 514: and 3 515: she 3 516: knew 4 517: he 2 518: would 5 519: probably 8 520: not 3 521: be 2 522: able 4 523: to 2 524: understand, 11 525: but 3 526: might 5 527: some 4 528: day 3 529: forgive 7 530: her, 4 531: and 3 532: be 2 533: grateful 8 534: to 2 535: her, 4 536: and 3 537: she 3 538: expected, 9 539: absolutely 10 540: unexpectedly, 13 541: to 2 542: be 2 543: married 7 544: in 2 545: the 3 546: spring. 7 547: She 3 548: loved 5 549: him 3 550: as 2 551: always, 7 552: but 3 553: she 3 554: realized 8 555: now 3 556: it 2 557: was 3 558: only 4 559: a 1 560: boy 3 561: and 3 562: girl 4 563: love. 5 564: She 3 565: hoped 5 566: he 2 567: would 5 568: have 4 569: a 1 570: great 5 571: career, 7 572: and 3 573: believed 8 574: in 2 575: him 3 576: absolutely. 11 577: She 3 578: knew 4 579: it 2 580: was 3 581: for 3 582: the 3 583: best. 5 584: The 3 585: major 5 586: did 3 587: not 3 588: marry 5 589: her 3 590: in 2 591: the 3 592: spring, 7 593: or 2 594: any 3 595: other 5 596: time. 5 597: Luz 3 598: never 5 599: got 3 600: an 2 601: answer 6 602: to 2 603: the 3 604: letter 6 605: to 2 606: Chicago 7 607: about 5 608: it. 3 609: A 1 610: short 5 611: time 4 612: after 5 613: he 2 614: contracted 10 615: gonorrhea 9 616: from 4 617: a 1 618: sales 5 619: girl 4 620: in 2 621: a 1 622: loop 4 623: department 10 624: store 5 625: while 5 626: riding 6 627: in 2 628: a 1 629: taxicab 7 630: through 7 631: Lincoln 7 632: Park. 5  ---- sample.txt ---- 0: the 3 1: large 5 2: brown 5 3: fox 3 4: jumped 6 5: over 4 6: the 3 7: lazy 4 8: dog 3  "    
    if [ "$res" == "$expect"  ];
    then
	echo -e "$green pass $nc"
    else
	echo -e "$red FAIL $nc"
    fi

    echo -n -e "#> valgrind ./wordcounter sample.txt\t\t\t"
    res="$( valgrind ./wordcounter sample.txt 2>&1  | grep 'no leaks are possible')"
    if [ ! -z "$res" ]
    then
	echo -e "$green pass $nc"
    else
	echo -e "$red FAIL $nc"
    fi

    echo -n -e "#> valgrind ./wordcounter hemmingway.txt\t\t"
    res="$( valgrind ./wordcounter hemmingway.txt 2>&1  | grep 'no leaks are possible')"
    expect="0 bytes"
    if [ ! -z "$res" ]
    then
	echo -e "$green pass $nc"
    else
	echo -e "$red FAIL $nc"
    fi

    echo -n -e "#> valgrind ./wordcounter hemmingway.txt sample.txt\t"
    res="$( valgrind ./wordcounter hemmingway.txt sample.txt 2>&1  | grep 'no leaks are possible')"
    expect="0 bytes"
    if [ ! -z "$res" ]
    then
	echo -e "$green pass $nc"
    else
	echo -e "$red FAIL $nc"
    fi
    
    cd ..

}


test_sysprog () {
    echo "--- Test Sys-Prog ---"
    cd sys-prog
    
    echo -n -e "#> ./read-struct simple-db \t\t\t\t"
    res="$(./read-struct simple-db | tr '\n' ' ')"
    expect="Name: Aviv, Adam Bal: 1000 Crd: 20 "
    if [ "$res" == "$expect"  ];
    then
	echo -e "$green pass $nc"
    else
	echo -e "$red FAIL $nc"
    fi

    echo -n -e "#> ./read-struct bank-db \t\t\t\t"
    res="$(./read-struct bank-db | tr '\n' ' ')"
    expect="Name: Aviv, Adam Bal: 2000 Crd: 10 Name: Blenkhorn, Kevin Bal: 11231 Crd: 54 Name: McDowell, Luke Bal: 5234 Crd: 10 Name: Chambers, Nate Bal: 0 Crd: 8755 Name: Sikora, Matt Bal: 22 Crd: 3872 Name: Watt, Eric Bal: 42 Crd: 42 "
    if [ "$res" == "$expect"  ];
    then
	echo -e "$green pass $nc"
    else
	echo -e "$red FAIL $nc"
    fi

    echo -n -e "#> ./read-struct BAD_FILE\t\t\t\t"
    res="$(./read-struct BAD_FILE 2>&1)"
    if [ ! -z "$res" ];
    then
	echo -e "$green pass $nc"
    else
	echo -e "$red FAIL $nc"
    fi

}

test_bash

echo 

test_cprog

echo

test_sysprog

