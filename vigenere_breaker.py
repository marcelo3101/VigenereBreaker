en_frequencies = [0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,
					  0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,
					  0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,
					  0.00978, 0.02360, 0.00150, 0.01974, 0.00074]

pt_frequencies = [0.1463, 0.0104, 0.0388, 0.0499, 0.1257, 0.0102, 0.0130, 0.0128, 
                 0.0618, 0.0040, 0.0002, 0.0278, 0.0474, 0.0505, 0.1073, 0.0252,
                 0.012, 0.0653, 0.0781, 0.0434, 0.0463, 0.0167, 0.0001, 0.0021,
                 0.0001, 0.0047]

letters = 'abcdefghijklmnopqrstuvwxyz'

def filter_string(string):
  string = ''.join(x.lower() for x in string if x.isalpha())
  return string

def show_coincidences(cipherText):
    counter = 0
    cipherLength = len(cipherText)
    copy = cipherText
    for offset in range(1, cipherLength//2):
        j = 0
        for i in range(offset, cipherLength):
            if cipherText[i] == copy[j]:
                counter += 1
            j+=1
        print(str(offset) + ": " + str(counter))
        counter = 0

def get_c(sequence):
	
    N = float(len(sequence))
    frequency_sum = 0.0
    for letter in letters:
	    frequency_sum+= sequence.count(letter) * (sequence.count(letter)-1)
    if N*(N-1) <= 0: index = frequency_sum/N
    else: index = frequency_sum/(N*(N-1))
    return index

def probable_key_length(ciphertext):
    coincidences = []
    for guess in range(21):
        coincidence_sum = 0.0
        average = 0.0
        for i in range(guess):
            letter_sequence = ""
            for j in range(0, len(ciphertext[i:]), guess):
                letter_sequence += ciphertext[i+j]
            coincidence_sum = get_c(letter_sequence)
        if not guess == 0:
            average = coincidence_sum/guess
        coincidences.append(average)
    print_coincidences(coincidences)
   

def print_coincidences(coincidences_array):
    for i in range(len(coincidences_array)):
        print(str(i) + ": " + str(coincidences_array[i]))

def freq_analysis(seq, en):
    chi_squared_array = [0] * 26
    if (en == True): letter_frequencies = en_frequencies
    else: letter_frequencies = pt_frequencies
    for i in range(26):
        sum_sq = 0.0
        sequence_offset = [chr(((ord(seq[j])-97-i)%26)+97) for j in range(len(seq))]
        c = [0] * 26
        for l in sequence_offset:
            c[ord(l) - ord('a')] += 1
        for j in range(26):
            c[j] *= (1.0/float(len(seq)))
        for j in range(26):
            sum_sq+=((c[j] - float(letter_frequencies[j]))**2)/float(letter_frequencies[j])
        chi_squared_array[i] = sum_sq
    shift = chi_squared_array.index(min(chi_squared_array))
    return chr(shift+97)

def get_key(ciphertext, key_length, en):
	key = ''
	for i in range(int(key_length)):
		sequence=""
		for j in range(0,len(ciphertext[i:]), int(key_length)):
			sequence+=ciphertext[i+j]
		key += freq_analysis(sequence, en)
	return key

def main():
    language = input("Digite 'en' para inglês e 'pt' para português: ")
    en = True
    if language == 'pt':
        en = False
    ciphertext_unfiltered = input("Digite o texto cifrado: ")
    ciphertext = filter_string(ciphertext_unfiltered)
    probable_key_length(ciphertext)
    key_length_guess = input("Digite o tamanho da chave: ")
    print(get_key(ciphertext, key_length_guess, en))

if __name__ == '__main__':
    main()