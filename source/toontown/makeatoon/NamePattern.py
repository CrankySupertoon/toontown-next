from direct.stdpy.file import open
import random, string

lines = '''
0*0*Baron
1*0*Duke
2*0*King
3*0*Master
4*0*Mister
5*0*Prince
6*0*Sir
7*1*Aunt
8*1*Granny
9*1*Lady
10*1*Miss
11*1*Princess
12*1*Queen
13*2*Captain
14*2*Colonel
15*2*Cool
16*2*Crazy
17*2*Deputy
18*2*Dippy
19*2*Doctor
20*2*Fat
21*2*Good ol'
22*2*Little
23*2*Loopy
24*2*Loud
25*2*Noisy
26*2*Prof.
27*2*Sheriff
28*2*Silly
29*2*Skinny
30*2*Super
31*2*Ugly
32*2*Weird
33*3*Alvin
34*3*Astro
35*3*Barney
36*3*Bart
37*3*Beppo
38*3*Bert
39*3*Bonzo
40*3*Buford
41*3*Bunky
42*3*Buster
43*3*Butch
44*3*Buzz
45*3*Cecil
46*3*Chester
47*3*Chip
48*3*Chipper
49*3*Clancy
50*3*Clarence
51*3*Cliff
52*3*Clyde
53*3*Dudley
54*3*Duke
55*3*Ernie
56*3*Felix
57*3*Fritz
58*3*Graham
59*3*Harvey
60*3*Hector
61*3*Huey
62*3*Jacques
63*3*Jake
64*3*Knuckles
65*3*Lancelot
66*3*Leroy
67*3*Lionel
68*3*Lloyd
69*3*Louie
70*3*Mac
71*3*Max
72*3*Milton
73*3*Moe
74*3*Monty
75*3*Ned
76*3*Orville
77*3*Oscar
78*3*Oswald
79*3*Ozzie
80*3*Pierre
81*3*Reggie
82*3*Ricky
83*3*Rocco
84*3*Rollie
85*3*Romeo
86*3*Rusty
87*3*Sammie
88*3*Skip
89*3*Skipper
90*3*Skippy
91*3*Spike
92*3*Stinky
93*3*Teddy
94*3*Tom
95*3*Waldo
96*3*Wally
97*3*Wilbur
98*4*Bonnie
99*4*Bubbles
100*4*Candy
101*4*Clover
102*4*Cuddles
103*4*Daffodil
104*4*Daphne
105*4*Dee Dee
106*4*Dottie
107*4*Ginger
108*4*Gwen
109*4*Ladybug
110*4*Lily
111*4*Marigold
112*4*Maxie
113*4*Melody
114*4*Mo Mo
115*4*Nutmeg
116*4*Olive
117*4*Peaches
118*4*Pearl
119*4*Penny
120*4*Petunia
121*4*Rainbow
122*4*Raven
123*4*Robin
124*4*Rosie
125*4*Roxy
126*4*Sadie
127*4*Sally
128*4*Sandy
129*4*Taffy
130*4*Trixie
131*4*Ursula
132*4*Valentine
133*4*Vicky
134*4*Violet
135*4*Willow
136*5*B.D.
137*5*Banjo
138*5*Batty
139*5*Beany
140*5*Bebop
141*5*Bingo
142*5*Binky
143*5*Biscuit
144*5*Bizzy
145*5*Blinky
146*5*Bongo
147*5*Bonkers
148*5*Boo Boo
149*5*Bouncey
150*5*Bumpy
151*5*C.J.
152*5*C.W.
153*5*Chirpy
154*5*Chunky
155*5*Coconut
156*5*Comet
157*5*Corky
158*5*Corny
159*5*Cranky
160*5*Crazy
161*5*Cricket
162*5*Crumbly
163*5*Cuckoo
164*5*Curly
165*5*Daffy
166*5*Dinky
167*5*Dizzy
168*5*Domino
169*5*Drippy
170*5*Droopy
171*5*Dusty
172*5*Dynamite
173*5*Fancy
174*5*Fangs
175*5*Fireball
176*5*Flapjack
177*5*Flappy
178*5*Fleabag
179*5*Flip
180*5*Fluffy
181*5*Freckles
182*5*Frizzy
183*5*Furball
184*5*Goopy
185*5*Huddles
186*5*J.C.
187*5*Jazzy
188*5*Jellyroll
189*5*Kippy
190*5*Kit
191*5*Lefty
192*5*Lollipop
193*5*Loony
194*5*Loopy
195*5*Lucky
196*5*Mildew
197*5*Murky
198*5*Nutty
199*5*Pancake
200*5*Peanut
201*5*Peppy
202*5*Pickles
203*5*Pinky
204*5*Popcorn
205*5*Poppy
206*5*Presto
207*5*Rhubarb
208*5*Salty
209*5*Scooter
210*5*Skids
211*5*Skimpy
212*5*Slappy
213*5*Slippy
214*5*Slumpy
215*5*Smirky
216*5*Snappy
217*5*Sniffy
218*5*Snuffy
219*5*Soupy
220*5*Spiffy
221*5*Spotty
222*5*Spunky
223*5*Squeaky
224*5*Star
225*5*Stripey
226*5*Stubby
227*5*Tricky
228*5*Tubby
229*5*Von
230*5*Wacko
231*5*Wacky
232*5*Whiskers
233*5*Winky
234*5*Yippie
235*5*Z.Z.
236*5*Zany
237*5*Ziggy
238*5*Zilly
239*5*Zippety
240*5*Zippy
241*5*Zowie
242*6*Mac
243*6*Mc
244*7*Bagel
245*7*Banana
246*7*Bean
247*7*Beanie
248*7*Biggen
249*7*Bizzen
250*7*Blubber
251*7*Boingen
252*7*Bumber
253*7*Bumble
254*7*Bumpen
255*7*Cheezy
256*7*Crinkle
257*7*Crumble
258*7*Crunchen
259*7*Crunchy
260*7*Dandy
261*7*Dingle
262*7*Dizzen
263*7*Dizzy
264*7*Doggen
265*7*Dyno
266*7*Electro
267*7*Feather
268*7*Fiddle
269*7*Fizzle
270*7*Flippen
271*7*Flipper
272*7*Frinkel
273*7*Fumble
274*7*Funny
275*7*Fuzzy
276*7*Giggle
277*7*Glitter
278*7*Google
279*7*Grumble
280*7*Gumdrop
281*7*Huckle
282*7*Hula
283*7*Jabber
284*7*Jeeper
285*7*Jinx
286*7*Jumble
287*7*Kooky
288*7*Lemon
289*7*Loopen
290*7*Mac
291*7*Mc
292*7*Mega
293*7*Mizzen
294*7*Nickel
295*7*Nutty
296*7*Octo
297*7*Paddle
298*7*Pale
299*7*Pedal
300*7*Pepper
301*7*Petal
302*7*Pickle
303*7*Pinker
304*7*Poodle
305*7*Poppen
306*7*Precious
307*7*Pumpkin
308*7*Purple
309*7*Rhino
310*7*Robo
311*7*Rocken
312*7*Ruffle
313*7*Smarty
314*7*Sniffle
315*7*Snorkel
316*7*Sour
317*7*Spackle
318*7*Sparkle
319*7*Squiggle
320*7*Super
321*7*Thunder
322*7*Toppen
323*7*Tricky
324*7*Tweedle
325*7*Twiddle
326*7*Twinkle
327*7*Wacky
328*7*Weasel
329*7*Whisker
330*7*Whistle
331*7*Wild
332*7*Witty
333*7*Wonder
334*7*Wrinkle
335*7*Ziller
336*7*Zippen
337*7*Zooble
338*8*bee
339*8*berry
340*8*blabber
341*8*bocker
342*8*boing
343*8*boom
344*8*bounce
345*8*bouncer
346*8*brains
347*8*bubble
348*8*bumble
349*8*bump
350*8*bumper
351*8*chomp
352*8*corn
353*8*crash
354*8*crumbs
355*8*crump
356*8*crunch
357*8*doodle
358*8*dorf
359*8*face
360*8*fidget
361*8*fink
362*8*fish
363*8*flap
364*8*flapper
365*8*flinger
366*8*flip
367*8*flipper
368*8*foot
369*8*fuddy
370*8*fussen
371*8*gadget
372*8*gargle
373*8*gloop
374*8*glop
375*8*goober
376*8*goose
377*8*grooven
378*8*hoffer
379*8*hopper
380*8*jinks
381*8*klunk
382*8*knees
383*8*marble
384*8*mash
385*8*monkey
386*8*mooch
387*8*mouth
388*8*muddle
389*8*muffin
390*8*mush
391*8*nerd
392*8*noodle
393*8*nose
394*8*nugget
395*8*phew
396*8*phooey
397*8*pocket
398*8*poof
399*8*pop
400*8*pounce
401*8*pow
402*8*pretzel
403*8*quack
404*8*roni
405*8*scooter
406*8*screech
407*8*smirk
408*8*snooker
409*8*snoop
410*8*snout
411*8*socks
412*8*speed
413*8*spinner
414*8*splat
415*8*sprinkles
416*8*sticks
417*8*stink
418*8*swirl
419*8*teeth
420*8*thud
421*8*toes
422*8*ton
423*8*toon
424*8*tooth
425*8*twist
426*8*whatsit
427*8*whip
428*8*wig
429*8*woof
430*8*zaner
431*8*zap
432*8*zapper
433*8*zilla
434*8*zoom
'''

TITLE_M = '0'
TITLE_F = '1'
TITLE_NEUTRAL = '2'
FIRST_NAME_M = '3'
FIRST_NAME_F = '4'
FIRST_NAME_NEUTRAL = '5'
CAP_PREFIX = '6'
LAST_NAME_PREFIX = '7'
LAST_NAME_SUFFIX = '8'

PART_LIST = ('title', 'first', 'last-prefix', 'last-suffix')

class NamePattern:

    def __init__(self, *a, **kw):
        names = (
            line.strip().split('*')
            for line in filter(None, lines.replace('\r', '\n').split('\n'))
            if not line.startswith('#')
        )
        self.nameDict = {}
        self.idDict = {}
        self.globalIdDict = {}
        for nameId, part, name in names:
            self.nameDict.setdefault(part, []).append(name)
            self.idDict.setdefault(part, {})
            self.idDict[part][name] = nameId
            self.globalIdDict[int(nameId)] = name
        for part in self.nameDict:
            self.nameDict[part].sort()

    def fetchAll(self, gender, part=None):
        if part == 'title':
            titleKey = TITLE_M if gender == 'm' else TITLE_F
            return self.nameDict[titleKey] + self.nameDict[TITLE_NEUTRAL]
        elif part == 'first':
            firstNameKey = FIRST_NAME_M if gender == 'm' else FIRST_NAME_F
            return (self.nameDict[firstNameKey] +
                    self.nameDict[FIRST_NAME_NEUTRAL])
        elif part == 'last-prefix':
            return self.nameDict[CAP_PREFIX] + self.nameDict[LAST_NAME_PREFIX]
        elif part == 'last-suffix':
            return self.nameDict[LAST_NAME_SUFFIX]

    def generateRandomToonName(self, gender):
        titlePart = None
        if random.random() > 0.5:
            titles = self.fetchAll(gender, 'title')
            titlePart = random.randint(0, len(titles) - 1)
        firsts = self.fetchAll(gender, 'first')
        firstPart = random.randint(0, len(firsts) - 1)
        lastPrefixPart = None
        lastSuffixPart = None
        if random.random() > 0.5:
            lastPrefixes = self.fetchAll(gender, 'last-prefix')
            lastPrefixPart = random.randint(0, len(lastPrefixes) - 1)
            lastSuffixes = self.fetchAll(gender, 'last-suffix')
            lastSuffixPart = random.randint(0, len(lastSuffixes) - 1)
        return (titlePart, firstPart, lastPrefixPart, lastSuffixPart)

    def getNameString(self, gender, nameParts):
        (titlePart, firstPart, lastPrefixPart, lastSuffixPart) = nameParts
        if titlePart not in (-1, None):
            titles = self.fetchAll(gender, 'title')
            titlePart = titles[titlePart]
        else:
            titlePart = ''
        firsts = self.fetchAll(gender, 'first')
        firstPart = firsts[firstPart]
        if lastPrefixPart not in (-1, None) and lastSuffixPart not in (-1, None):
            lastPrefixes = self.fetchAll(gender, 'last-prefix')
            lastPrefixPart = lastPrefixes[lastPrefixPart]
            lastSuffixes = self.fetchAll(gender, 'last-suffix')
            lastSuffixPart = lastSuffixes[lastSuffixPart]
        else:
            lastPrefixPart = ''
            lastSuffixPart = ''
        name = (titlePart + ' ' + firstPart + ' ' +
                lastPrefixPart + lastSuffixPart)
        return unicode(name.decode('latin-1').strip()).replace('\n', '')

    def getStringParts(self, gender, nameParts):
        (titlePart, firstPart, lastPrefixPart, lastSuffixPart) = nameParts
        if titlePart not in (-1, None):
            titles = self.fetchAll(gender, 'title')
            titlePart = titles[titlePart]
        else:
            titlePart = ''
        firsts = self.fetchAll(gender, 'first')
        firstPart = firsts[firstPart]
        if lastPrefixPart not in (-1, None) and lastSuffixPart not in (-1, None):
            lastPrefixes = self.fetchAll(gender, 'last-prefix')
            lastPrefixPart = lastPrefixes[lastPrefixPart]
            lastSuffixes = self.fetchAll(gender, 'last-suffix')
            lastSuffixPart = lastSuffixes[lastSuffixPart]
        else:
            lastPrefixPart = ''
            lastSuffixPart = ''
        return [titlePart, firstPart, lastPrefixPart, lastSuffixPart]

    def getNameId(self, namePart, nameString):
        parts = self.fetchAll('m', namePart) + self.fetchAll('f', namePart)
        parts.sort()
        return parts.index(nameString)
        
    def getPartId(self, part, name, gender):
        if not name:
            return -1
            
        partIdx = []
        
        if part == 'last-prefix':
            partIdx = [LAST_NAME_PREFIX]
            
        elif part == 'last-suffix':
            partIdx = [LAST_NAME_SUFFIX]
                
        elif gender == 'm':
            if part == 'title':
                partIdx = [TITLE_M, TITLE_NEUTRAL]
                
            elif part == 'first':
                partIdx = [FIRST_NAME_M, FIRST_NAME_NEUTRAL]
                
        elif gender == 'f':
            if part == 'title':
                partIdx = [TITLE_F, TITLE_NEUTRAL]
                
            elif part == 'first':
                partIdx = [FIRST_NAME_F, FIRST_NAME_NEUTRAL]
                                
        for idx in partIdx:
            ls = self.idDict[idx]
            if name in ls:
                return int(ls[name])
                
        return -1
        
    def getStringFromIndexes(self, gender, (title, first, lastPrefix, lastSuffix)):
        titles = [self.getPartId('title', x, gender) for x in self.fetchAll(gender, 'title')]
        firsts = [self.getPartId('first', x, gender) for x in self.fetchAll(gender, 'first')]
        lastPrefixes = [self.getPartId('last-prefix', x, gender) for x in self.fetchAll(gender, 'last-prefix')]
        lastSuffixes = [self.getPartId('last-suffix', x, gender) for x in self.fetchAll(gender, 'last-suffix')]
        
        name = []
        if title not in (-1, None):
            if title in titles:
                name.append(self.globalIdDict.get(title, ''))
                
        if first not in (-1, None):
            if first in firsts:
                name.append(self.globalIdDict.get(first, ''))
        
        if lastPrefix not in (-1, None):
            if lastSuffix not in (-1, None):
                if lastPrefix in lastPrefixes and lastSuffix in lastSuffixes:
                    name.append(self.globalIdDict.get(lastPrefix, '') + self.globalIdDict.get(lastSuffix, ''))
                    
        return " ".join(name)
            
def randomName(boy=0, girl=0):
    gender = 'm' if boy else 'f'
    pat = NamePattern()
    return pat.getNameString([], pat.generateRandomToonName(gender))
    