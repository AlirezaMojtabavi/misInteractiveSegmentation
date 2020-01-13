uniform vec3 startPoint;
uniform vec3 endPoint;
uniform vec3 currentPoint;
uniform vec3 interSectionPoint;
uniform vec3 normalPlane;
uniform vec3 planeNormal;
uniform vec3 imageExtent;
uniform float planRadius;
uniform float targetRadius;
uniform vec3 screwColor;
uniform float borderInlineOpacity;
uniform float borderOpacity;
uniform bool displayProjection;
uniform bool displayCrossSection;
uniform float dashlineSize;
uniform vec4 intersectioncolor;



varying vec4 vTexCoord1;

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

struct Sphere
{
	float Radius;
	vec3 Center;
};

bool IsInPlanROI(Roi, CylindricalPoint, bool);
bool IsOnCircle(Sphere s, vec3 point, float thickness);
CylindricalPoint ConvertToCylindricalCoord(vec3 point, vec3 startPoint, vec3 endPoint);
vec3 ProjectPointOnPlane(vec3 point, vec3 normal, vec3 planePoint);
float PointPositionRelativeToPlane(vec3 point, vec3 pointOnPlane, vec3 planeNormal);

void main(void)
{
	vec3 X = vec3(vTexCoord1.x * imageExtent.x, vTexCoord1.y * imageExtent.y, vTexCoord1.z * imageExtent.z);

	vec3 normalizedVec = planeNormal / length(planeNormal);
	vec3 Ap = ProjectPointOnPlane(startPoint, normalizedVec, X);
	vec3 Bp = ProjectPointOnPlane(endPoint, normalizedVec, X);
	vec3 ApBp = Bp - Ap;
	CylindricalPoint projectedPoint = ConvertToCylindricalCoord(X, Ap, Bp);

	Roi planProjRoi;
	planProjRoi.MinLength = 0.0;
	planProjRoi.MaxLength = length(Bp - Ap);
	planProjRoi.MinRadius = 0.;
	planProjRoi.MaxRadius = planRadius / 2.;

	Sphere targetRegion;
	targetRegion.Center = endPoint;
	targetRegion.Radius = targetRadius;

	bool oblique = true;
	if ((normalPlane[0] == 1.0 || normalPlane[0] == 0.0 || normalPlane[0] == -1.0 || normalPlane[0] == -0.0) &&
		(normalPlane[1] == 1.0 || normalPlane[1] == 0.0 || normalPlane[1] == -1.0 || normalPlane[1] == -0.0) &&
		(normalPlane[2] == 1.0 || normalPlane[2] == 0.0 || normalPlane[2] == -1.0 || normalPlane[2] == -0.0))
		oblique = false;
	bool isTargetEntryOnOnePlane = false;
	if (((startPoint[0] == endPoint[0]) && (normalPlane[0] == 1.0 || normalPlane[0] == -1.0)) ||
		((startPoint[1] == endPoint[1]) && (normalPlane[1] == 1.0 || normalPlane[1] == -1.0)) ||
		((startPoint[2] == endPoint[2]) && (normalPlane[2] == 1.0 || normalPlane[2] == -1.0)))
		isTargetEntryOnOnePlane = true;

	double lenght = length(X - interSectionPoint);
	float mod = (projectedPoint.LineParam - (6.0 * floor(projectedPoint.LineParam / 6.0)));
	if ((lenght < 3.0) && (projectedPoint.LineParam > planProjRoi.MinLength - 1.0) && (projectedPoint.LineParam < planProjRoi.MaxLength + 1.0) && !oblique && !isTargetEntryOnOnePlane)
	{
		gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
	}
	else if (IsInPlanROI(planProjRoi, projectedPoint, displayProjection))
	{
		vec3 AB = endPoint - startPoint;
		vec3 normalizedab = normalize(AB);
		float coef = length(AB) / length(ApBp);
		vec3 projectedPointWC = startPoint + projectedPoint.LineParam* coef*normalizedab;
		vec3 w = projectedPointWC - interSectionPoint;
		float distance = dot(normalizedVec, w) / length(normalizedVec);
		if (distance > 0.0 && !oblique)
			gl_FragColor = vec4(screwColor.r, screwColor.g, screwColor.b, 1);
		else if (mod < 2.0)
			gl_FragColor = vec4(screwColor.r, screwColor.g, screwColor.b, 1);
	}
	else if (IsOnCircle(targetRegion, X, 1.0))
	{
		gl_FragColor = vec4(screwColor.r, screwColor.g, screwColor.b, borderOpacity);
	}
	else
	{
		gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
	}
}

vec3 ProjectPointOnPlane(vec3 point, vec3 normal, vec3 planePoint)
{
	return cross(normal, cross(point, normal)) + dot(planePoint, normal) * normal;
}

CylindricalPoint ConvertToCylindricalCoord(vec3 point, vec3 startPoint, vec3 endPoint)
{
	vec3 AB = endPoint - startPoint;
	vec3 AX = point - startPoint;

	float lengthAB = length(AB);
	float lineParam = dot(AX, AB) / lengthAB;
	float distance = sqrt(dot(AX, AX) - pow(lineParam, 2));

	CylindricalPoint projectedPoint;
	projectedPoint.LineParam = lineParam;
	projectedPoint.Distance = distance;

	return projectedPoint;
}

bool IsInPlanROI(Roi roi, CylindricalPoint point, bool isEnable)
{
	if (isEnable)
	{
		return  (point.LineParam > roi.MinLength) && (point.LineParam < roi.MaxLength) && (point.Distance < roi.MaxRadius) && (point.Distance > roi.MinRadius);
	}
	else
	{
		return false;
	}
}

bool IsOnCircle(Sphere sphere, vec3 point, float thickness)
{
	vec3 pVec = point - sphere.Center;
	float len = length(pVec);
	return len < sphere.Radius && len >(sphere.Radius - thickness);
}

float PointPositionRelativeToPlane(vec3 point, vec3 pointOnPlane, vec3 planeNormal)
{
	vec3 v = pointOnPlane - point;
	return dot(v, planeNormal);
}