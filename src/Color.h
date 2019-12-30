class Color {
public:

	float red;
	float blue;
	float green;

	Color(float r, float g, float b);

	friend bool operator== (const Color& c1, const Color& c2);
	friend Color operator+ (const Color& c1, const Color& c2);
	friend Color operator- (const Color& c1, const Color& c2);
	friend Color operator* (const Color& c, const float scalar);
	friend Color operator* (const Color& c1, const Color& c2);
};