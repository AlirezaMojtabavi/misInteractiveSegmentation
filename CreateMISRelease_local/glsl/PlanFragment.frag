uniform vec3 startPoint;
uniform vec3 endPoint;
uniform vec3 imageExtent;

uniform float planRadius;
varying vec4 vTexCoord1;
uniform vec3 screwColor;
uniform float borderInlineOpacity;
uniform float borderOpacity;
struct Roi
{
	float MinRadius;
	float MaxRadius;
	float MinLength;
	float MaxLength;
};

struct CylindricalPoint
{
	float LineParam;
	float Distance;
};

struct Plan
{
	float Length;
	float Radius;
	float BorderThickness;
};


float ExpCurve(float, float, float);
float SawToothFunction(float);
float PlanCurve(float, Plan);

bool IsInPlanROI(Roi, CylindricalPoint);
bool IsOnPlanBorder(CylindricalPoint, Plan);
bool IsInLayer(CylindricalPoint, Plan, Roi);
bool ISPin(CylindricalPoint, Plan, Roi);
bool IsInPlanBorder(CylindricalPoint, Plan, Roi);

void main(void)
{
	vec3 X = vec3(vTexCoord1.x * imageExtent.x, vTexCoord1.y * imageExtent.y, vTexCoord1.z * imageExtent.z);
	vec3 AB = endPoint - startPoint;
	float lengthAB = length(AB);
	vec3 normalizeAB = normalize(AB);
	vec3 newStartPoint = startPoint - (normalizeAB * (0.1*lengthAB));
	AB = endPoint - newStartPoint;
	lengthAB = length(AB);
	vec3 AX = X - newStartPoint;
	vec3 BX = X - endPoint;

	float lineParam = dot(AX, AB) / lengthAB;
	float distance = sqrt(dot(AX, AX) - pow(lineParam, 2));

	CylindricalPoint point;
	point.LineParam = lineParam;
	point.Distance = distance;

	Plan plan;
	plan.Length = lengthAB;
	plan.Radius = planRadius;
	plan.BorderThickness = 0.3;

	float layerDistance = 1.0;

	Roi layer1;
	layer1.MinLength = plan.Length;
	layer1.MinRadius = plan.Radius;
	layer1.MaxLength = plan.Length + layerDistance;
	layer1.MaxRadius = plan.Radius + layerDistance;

	Roi layer2;
	layer2.MinLength = layer1.MaxLength;
	layer2.MaxLength = layer1.MaxLength + layerDistance;
	layer2.MinRadius = layer1.MaxRadius;
	layer2.MaxRadius = layer1.MaxRadius + layerDistance;

	Roi planRoi;
	planRoi.MinLength = -.01;
	planRoi.MaxLength = layer2.MaxLength;
	planRoi.MinRadius = 0.0;
	planRoi.MaxRadius = layer2.MaxRadius;

	if (!IsInPlanROI(planRoi, point))
		gl_FragColor = vec4(0., 0., 0., 0.);
	else if (ISPin(point, plan, layer1))
		gl_FragColor = vec4(0., 0., 0., 0.);
	else if (IsInPlanBorder(point, plan, layer1))
		gl_FragColor = vec4(screwColor.r, screwColor.g, screwColor.b, borderInlineOpacity);
	else if (IsOnPlanBorder(point, plan))
		gl_FragColor = vec4(screwColor.r, screwColor.g, screwColor.b, borderOpacity);
	else if (IsInLayer(point, plan, layer1))
		gl_FragColor = vec4(1.0, 1.0, 0.0, .15);


}

float ExpCurve(float y0, float length, float x)
{
	float coefficient = y0 / (pow(1 + length, 1.0 / 10.0));
	return coefficient * pow(1 + length - x, 1.0 / 10.0);
}

float SawToothFunction(float x)
{
	float newLineParam = x * 0.5;
	return abs((newLineParam - floor(newLineParam)) - 0.5);
}

float PlanCurve(float x, Plan plan)
{
	float y0 = plan.Radius - plan.BorderThickness;
	double swt = 0;
	if ((x / plan.Length) > .1)
		swt = (pow(SawToothFunction(x), 2.0) * 3.7) - .8;
	else
		y0 += 1.3;

	return ExpCurve(y0, plan.Length, x) + swt;
}

bool IsInPlanROI(Roi roi, CylindricalPoint point)
{
	return (point.LineParam > roi.MinLength) && (point.LineParam < roi.MaxLength) && (point.Distance < roi.MaxRadius);
}

bool IsOnPlanBorder(CylindricalPoint point, Plan plan)
{
	float xNormal = point.LineParam / plan.Length;
	float sawtooth = PlanCurve(point.LineParam, plan);

	return (point.Distance < (sawtooth + plan.BorderThickness) && point.Distance > sawtooth) ||
		(point.Distance < sawtooth && (xNormal < 0.1 || xNormal > 0.99));
}

bool IsInLayer(CylindricalPoint point, Plan plan, Roi layer)
{
	float innerBorder = PlanCurve(point.LineParam, plan);
	float outerBorder = ExpCurve(layer.MaxRadius, layer.MaxLength, point.LineParam);

	return (point.Distance < outerBorder && point.Distance > innerBorder) ||
		(point.Distance < outerBorder && point.LineParam > layer.MinLength && point.LineParam < layer.MaxLength);

}

bool ISPin(CylindricalPoint point, Plan plan, Roi layer)
{
	float innerBorder = PlanCurve(point.LineParam, plan);
	float outerBorder = ExpCurve(layer.MaxRadius, layer.MaxLength, point.LineParam);

	return !((point.Distance < outerBorder && point.Distance > innerBorder) || (point.Distance < outerBorder && point.LineParam > layer.MinLength && point.LineParam < layer.MaxLength)) &&
		(point.Distance < innerBorder - 0.7) &&
		((point.LineParam / plan.Length) > .0 && (point.LineParam / plan.Length) < .05);
}

bool IsInPlanBorder(CylindricalPoint point, Plan plan, Roi layer)
{
	float innerBorder = PlanCurve(point.LineParam, plan);
	float outerBorder = ExpCurve(layer.MaxRadius, layer.MaxLength, point.LineParam);

	return !((point.Distance < outerBorder && point.Distance > innerBorder) || (point.Distance < outerBorder && point.LineParam > layer.MinLength && point.LineParam < layer.MaxLength)) &&
		(point.Distance < innerBorder);
}

