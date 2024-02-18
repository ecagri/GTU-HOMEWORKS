import pywrapfst as fst

f = fst.Fst()
symbol_table = fst.SymbolTable()

s0 = f.add_state()
s1 = f.add_state()
s2 = f.add_state()
s3 = f.add_state()
s4 = f.add_state()
s5 = f.add_state()
s6 = f.add_state()
s7 = f.add_state()
s8 = f.add_state()
s10 = f.add_state()
s11 = f.add_state()
s12 = f.add_state()
s13 = f.add_state()
s14 = f.add_state()
s15 = f.add_state()
s16 = f.add_state()
s17 = f.add_state()
s18 = f.add_state()
s19 = f.add_state()
s20 = f.add_state()
s21 = f.add_state()
s22 = f.add_state()
s23 = f.add_state()
s24 = f.add_state()
s25 = f.add_state()
s26 = f.add_state()
s27 = f.add_state()
s28 = f.add_state()
s29 = f.add_state()
s30 = f.add_state()
s32 = f.add_state()
s33 = f.add_state()
s34 = f.add_state()
s35 = f.add_state()
s36 = f.add_state()
s37 = f.add_state()
s39 = f.add_state()
s40 = f.add_state()
s41 = f.add_state()
s42 = f.add_state()
s43 = f.add_state()
s44 = f.add_state()
s45 = f.add_state()
s46 = f.add_state()
s47 = f.add_state()
s48 = f.add_state()
s49 = f.add_state()
s52 = f.add_state()
s54 = f.add_state()
s55 = f.add_state()


# ARABA TAŞIT KAMYON FOLYO TAKI ÇİVİ ÇARE ÜLKÜ EV ÇÖP 

for letter in ['a', 'r', 'b', 't', 'ş', 'ı', 'k', 'm', 'y', 'o', 'n', 'u', 't', 'p', 'e', 'v', 's', 'i', 'l', 'g', 'y', 'ö', 'z', 'd', 'ç', 'i', 'ü', 'f']:
    symbol_table.add_symbol(letter)


symbol_table.add_symbol("sı")
symbol_table.add_symbol("su")
symbol_table.add_symbol("si")
symbol_table.add_symbol("sü")
symbol_table.add_symbol("ım")
symbol_table.add_symbol("ız")
symbol_table.add_symbol("iz")
symbol_table.add_symbol("uz")
symbol_table.add_symbol("üz")
symbol_table.add_symbol("lar")
symbol_table.add_symbol("ler")
symbol_table.add_symbol('a+N')
symbol_table.add_symbol('t+N')
symbol_table.add_symbol('n+N')
symbol_table.add_symbol('o+N')
symbol_table.add_symbol('ı+N')
symbol_table.add_symbol('i+N')
symbol_table.add_symbol('e+N')
symbol_table.add_symbol('ü+N')
symbol_table.add_symbol('v+N')
symbol_table.add_symbol('p+N')

symbol_table.add_symbol("+PL")
symbol_table.add_symbol('EPSILON')
symbol_table.add_symbol("+PSS")

f.set_input_symbols(symbol_table)
f.set_output_symbols(symbol_table)

# ARABA WORD #

f.add_arc(s0, fst.Arc(symbol_table.find('a'), symbol_table.find('a'), fst.Weight.One(f.weight_type()), s1))
f.add_arc(s1, fst.Arc(symbol_table.find('r'), symbol_table.find('r'), fst.Weight.One(f.weight_type()), s2))
f.add_arc(s2, fst.Arc(symbol_table.find('a'), symbol_table.find('a'), fst.Weight.One(f.weight_type()), s3))
f.add_arc(s3, fst.Arc(symbol_table.find('b'), symbol_table.find('b'), fst.Weight.One(f.weight_type()), s4))
f.add_arc(s4, fst.Arc(symbol_table.find('a'), symbol_table.find('a+N'), fst.Weight.One(f.weight_type()), s5))

# TAŞIT AND TAKI WORDS #

f.add_arc(s0, fst.Arc(symbol_table.find('t'), symbol_table.find('t'), fst.Weight.One(f.weight_type()), s11))
f.add_arc(s11, fst.Arc(symbol_table.find('a'), symbol_table.find('a'), fst.Weight.One(f.weight_type()), s12))
f.add_arc(s12, fst.Arc(symbol_table.find('ş'), symbol_table.find('ş'), fst.Weight.One(f.weight_type()), s13))
f.add_arc(s13, fst.Arc(symbol_table.find('ı'), symbol_table.find('ı'), fst.Weight.One(f.weight_type()), s14))
f.add_arc(s14, fst.Arc(symbol_table.find('t'), symbol_table.find('t+N'), fst.Weight.One(f.weight_type()), s15))

f.add_arc(s12, fst.Arc(symbol_table.find('k'), symbol_table.find('k'), fst.Weight.One(f.weight_type()), s30))
f.add_arc(s30, fst.Arc(symbol_table.find('ı'), symbol_table.find('ı+N'), fst.Weight.One(f.weight_type()), s5))

# KAMYON WORD #

f.add_arc(s0, fst.Arc(symbol_table.find('k'), symbol_table.find('k'), fst.Weight.One(f.weight_type()), s16))
f.add_arc(s16, fst.Arc(symbol_table.find('a'), symbol_table.find('a'), fst.Weight.One(f.weight_type()), s17))
f.add_arc(s17, fst.Arc(symbol_table.find('m'), symbol_table.find('m'), fst.Weight.One(f.weight_type()), s18))
f.add_arc(s18, fst.Arc(symbol_table.find('y'), symbol_table.find('y'), fst.Weight.One(f.weight_type()), s19))
f.add_arc(s19, fst.Arc(symbol_table.find('o'), symbol_table.find('o'), fst.Weight.One(f.weight_type()), s20))
f.add_arc(s20, fst.Arc(symbol_table.find('n'), symbol_table.find('n+N'), fst.Weight.One(f.weight_type()), s21))

# FOLYO WORD #

f.add_arc(s0, fst.Arc(symbol_table.find('f'), symbol_table.find('f'), fst.Weight.One(f.weight_type()), s25))
f.add_arc(s25, fst.Arc(symbol_table.find('o'), symbol_table.find('o'), fst.Weight.One(f.weight_type()), s26))
f.add_arc(s26, fst.Arc(symbol_table.find('l'), symbol_table.find('l'), fst.Weight.One(f.weight_type()), s27))
f.add_arc(s27, fst.Arc(symbol_table.find('y'), symbol_table.find('y'), fst.Weight.One(f.weight_type()), s28))
f.add_arc(s28, fst.Arc(symbol_table.find('o'), symbol_table.find('o+N'), fst.Weight.One(f.weight_type()), s29))

# ÇİVİ WORD #

f.add_arc(s0, fst.Arc(symbol_table.find('ç'), symbol_table.find('ç'), fst.Weight.One(f.weight_type()), s32))
f.add_arc(s32, fst.Arc(symbol_table.find('i'), symbol_table.find('i'), fst.Weight.One(f.weight_type()), s33))
f.add_arc(s33, fst.Arc(symbol_table.find('v'), symbol_table.find('v'), fst.Weight.One(f.weight_type()), s34))
f.add_arc(s34, fst.Arc(symbol_table.find('i'), symbol_table.find('i+N'), fst.Weight.One(f.weight_type()), s35))

# ÇARE WORD #

f.add_arc(s32, fst.Arc(symbol_table.find('a'), symbol_table.find('a'), fst.Weight.One(f.weight_type()), s36))
f.add_arc(s36, fst.Arc(symbol_table.find('r'), symbol_table.find('r'), fst.Weight.One(f.weight_type()), s37))
f.add_arc(s37, fst.Arc(symbol_table.find('e'), symbol_table.find('e+N'), fst.Weight.One(f.weight_type()), s35))

# ÇÖP WORD #

f.add_arc(s32, fst.Arc(symbol_table.find('ö'), symbol_table.find('ö'), fst.Weight.One(f.weight_type()), s39))
f.add_arc(s39, fst.Arc(symbol_table.find('p'), symbol_table.find('p+N'), fst.Weight.One(f.weight_type()), s40))

# EV WORD #

f.add_arc(s0, fst.Arc(symbol_table.find('e'), symbol_table.find('e'), fst.Weight.One(f.weight_type()), s41))
f.add_arc(s41, fst.Arc(symbol_table.find('v'), symbol_table.find('v+N'), fst.Weight.One(f.weight_type()), s42))

# ÜLKÜ #

f.add_arc(s0, fst.Arc(symbol_table.find('ü'), symbol_table.find('ü'), fst.Weight.One(f.weight_type()), s43))
f.add_arc(s43, fst.Arc(symbol_table.find('l'), symbol_table.find('l'), fst.Weight.One(f.weight_type()), s44))
f.add_arc(s44, fst.Arc(symbol_table.find('k'), symbol_table.find('k'), fst.Weight.One(f.weight_type()), s45))
f.add_arc(s45, fst.Arc(symbol_table.find('ü'), symbol_table.find('ü+N'), fst.Weight.One(f.weight_type()), s46))


# PLURAL SUFFIX 'LAR' #

f.add_arc(s5, fst.Arc(symbol_table.find('lar'), symbol_table.find('+PL'), fst.Weight.One(f.weight_type()), s6)) # ARABA TAKI#
f.add_arc(s15, fst.Arc(symbol_table.find('lar'), symbol_table.find('+PL'), fst.Weight.One(f.weight_type()), s6))  # TAŞIT #  
f.add_arc(s21, fst.Arc(symbol_table.find('lar'), symbol_table.find("+PL"), fst.Weight.One(f.weight_type()), s6)) # KAMYON #
f.add_arc(s29, fst.Arc(symbol_table.find('lar'), symbol_table.find("+PL"), fst.Weight.One(f.weight_type()), s6)) # FOLYO #

# PLURAL SUFFIX 'LER' #

f.add_arc(s35, fst.Arc(symbol_table.find('ler'), symbol_table.find('+PL'), fst.Weight.One(f.weight_type()), s47)) # ÇİVİ ÇARE #
f.add_arc(s40, fst.Arc(symbol_table.find('ler'), symbol_table.find("+PL"), fst.Weight.One(f.weight_type()), s47)) # ÇÖP #
f.add_arc(s42, fst.Arc(symbol_table.find('ler'), symbol_table.find("+PL"), fst.Weight.One(f.weight_type()), s47)) # EV #
f.add_arc(s46, fst.Arc(symbol_table.find('ler'), symbol_table.find("+PL"), fst.Weight.One(f.weight_type()), s47)) # ÜLKÜ #

# POSSESIVES AFTER PLURAL SUFFIX 'LER' #

f.add_arc(s47, fst.Arc(symbol_table.find('i'), symbol_table.find("+PSS"), fst.Weight.One(f.weight_type()), s48)) 
f.add_arc(s48, fst.Arc(symbol_table.find('m'), symbol_table.find("EPSILON"), fst.Weight.One(f.weight_type()), s49)) 
f.add_arc(s48, fst.Arc(symbol_table.find('n'), symbol_table.find("EPSILON"), fst.Weight.One(f.weight_type()), s49)) 
f.add_arc(s49, fst.Arc(symbol_table.find('iz'), symbol_table.find("EPSILON"), fst.Weight.One(f.weight_type()), s10)) 

# POSSESIVES WITHOUT PLURAL SUFFIX 'LER' #

f.add_arc(s35, fst.Arc(symbol_table.find('si'), symbol_table.find("+PSS"), fst.Weight.One(f.weight_type()), s10)) 
f.add_arc(s35, fst.Arc(symbol_table.find('m'), symbol_table.find("+PSS"), fst.Weight.One(f.weight_type()), s52)) 
f.add_arc(s35, fst.Arc(symbol_table.find('n'), symbol_table.find("+PSS"), fst.Weight.One(f.weight_type()), s52)) 
f.add_arc(s52, fst.Arc(symbol_table.find('iz'), symbol_table.find("EPSILON"), fst.Weight.One(f.weight_type()), s10)) 
f.add_arc(s42, fst.Arc(symbol_table.find('i'), symbol_table.find("+PSS"), fst.Weight.One(f.weight_type()), s48)) 
f.add_arc(s40, fst.Arc(symbol_table.find('ü'), symbol_table.find("+PSS"), fst.Weight.One(f.weight_type()), s54))
f.add_arc(s54, fst.Arc(symbol_table.find('m'), symbol_table.find("EPSILON"), fst.Weight.One(f.weight_type()), s55)) 
f.add_arc(s54, fst.Arc(symbol_table.find('n'), symbol_table.find("EPSILON"), fst.Weight.One(f.weight_type()), s55)) 
f.add_arc(s55, fst.Arc(symbol_table.find('üz'), symbol_table.find("EPSILON"), fst.Weight.One(f.weight_type()), s10)) 
f.add_arc(s46, fst.Arc(symbol_table.find('m'), symbol_table.find("+PSS"), fst.Weight.One(f.weight_type()), s55)) 
f.add_arc(s46, fst.Arc(symbol_table.find('n'), symbol_table.find("+PSS"), fst.Weight.One(f.weight_type()), s55)) 
f.add_arc(s46, fst.Arc(symbol_table.find('sü'), symbol_table.find("+PSS"), fst.Weight.One(f.weight_type()), s10)) 


# POSSESIVES AFTER PLURAL SUFFIX 'LAR' #

f.add_arc(s5, fst.Arc(symbol_table.find('sı'), symbol_table.find("+PSS"), fst.Weight.One(f.weight_type()), s10))
f.add_arc(s6, fst.Arc(symbol_table.find('ı'), symbol_table.find("+PSS"), fst.Weight.One(f.weight_type()), s7))
f.add_arc(s7, fst.Arc(symbol_table.find('m'), symbol_table.find('EPSILON'), fst.Weight.One(f.weight_type()), s8))
f.add_arc(s7, fst.Arc(symbol_table.find('n'), symbol_table.find('EPSILON'), fst.Weight.One(f.weight_type()), s8))
f.add_arc(s8, fst.Arc(symbol_table.find('ız'), symbol_table.find('EPSILON'), fst.Weight.One(f.weight_type()), s10))
f.add_arc(s5, fst.Arc(symbol_table.find('m'), symbol_table.find('+PSS'), fst.Weight.One(f.weight_type()), s8))
f.add_arc(s5, fst.Arc(symbol_table.find('n'), symbol_table.find('+PSS'), fst.Weight.One(f.weight_type()), s8))

# POSSESIVES WITHOUT PLURAL SUFFIX 'LAR' #


f.add_arc(s29, fst.Arc(symbol_table.find('su'), symbol_table.find("+PSS"), fst.Weight.One(f.weight_type()), s10))
f.add_arc(s29, fst.Arc(symbol_table.find('m'), symbol_table.find('+PSS'), fst.Weight.One(f.weight_type()), s23))
f.add_arc(s29, fst.Arc(symbol_table.find('n'), symbol_table.find('+PSS'), fst.Weight.One(f.weight_type()), s24))
f.add_arc(s21, fst.Arc(symbol_table.find('u'), symbol_table.find("+PSS"), fst.Weight.One(f.weight_type()), s22))
f.add_arc(s22, fst.Arc(symbol_table.find('m'), symbol_table.find('EPSILON'), fst.Weight.One(f.weight_type()), s23))
f.add_arc(s22, fst.Arc(symbol_table.find('n'), symbol_table.find('EPSILON'), fst.Weight.One(f.weight_type()), s24))
f.add_arc(s23, fst.Arc(symbol_table.find('uz'), symbol_table.find('EPSILON'), fst.Weight.One(f.weight_type()), s10))
f.add_arc(s24, fst.Arc(symbol_table.find('uz'), symbol_table.find('EPSILON'), fst.Weight.One(f.weight_type()), s10))
f.add_arc(s15, fst.Arc(symbol_table.find('ı'), symbol_table.find('+PSS'), fst.Weight.One(f.weight_type()), s7))


# SETTING START STATE #

f.set_start(s0)

# SETTING FINAL STATES #

f.set_final(s5) 
f.set_final(s6) 
f.set_final(s7)
f.set_final(s8)
f.set_final(s10)
f.set_final(s15) 
f.set_final(s21) 
f.set_final(s22)
f.set_final(s23)
f.set_final(s24)
f.set_final(s29) 
f.set_final(s35) 
f.set_final(s40) 
f.set_final(s42) 
f.set_final(s46) 
f.set_final(s47)
f.set_final(s48)
f.set_final(s49)
f.set_final(s52)
f.set_final(s54)
f.set_final(s55)

# CREATING DOT FILE #

dot_file = f"pluralFST.dot"
f.draw(dot_file, isymbols=symbol_table, osymbols=symbol_table, title="MY FST", portrait=True)

# TESTING WORDS IN DIFFERENT FORMS#

while True: 
    input_str = input("Enter the input:")
    if(input_str == ""):
        break
    output_labels = []
    prev = ""

    input_symbols = f.input_symbols()
    output_symbols = f.output_symbols()

    state = f.start()

    if input_symbols is None:
        print("Error: Input symbols are not defined in the FST.")
    else:
        for symbol in input_str:
            symbol_index = input_symbols.find(prev + symbol)
            prev += symbol
            if symbol_index != -1:        
                arc = None
                for a in f.arcs(state):
                    if a.ilabel == symbol_index:
                        arc = a
                        break
                if arc:
                    output_label = arc.olabel
                    if output_label != -1:
                     	if(output_symbols.find(output_label).decode('utf-8') != 'EPSILON'):
                     		output_labels.append(output_label)
                    state = arc.nextstate
                    prev = ""
        if f.final(state) != fst.Weight.Zero(f.weight_type()) and len(prev) == 0:
            output_str = ''.join([output_symbols.find(label).decode('utf-8') for label in output_labels])
            
            print(f"The lexical form of '{input_str}' is: '{output_str}' ")
        else:
            print(f"The word '{input_str}' is not accepted by the FST")

